#include "gameparser.h"

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "parserutils.h"
#include "pieceparser.h"
#include "moveparser.h"
#include "promotionparser.h"
#include "trackerupdateparser.h"

using namespace std;

#define CHECK(cond, error, msg) \
    if (cond) { \
        cout << msg << "\n"; \
        throw error; \
    }

#define PUSH_BLOCK(name, collectionName) \
    int size = blockSize(instr, 0); \
    vector <string> name; \
    int count = 0; \
    while (count < size) { \
        name.push_back(instr.front()); \
        POP_FRONT(instr); \
        count++; \
    } \
    collectionName.push_back(name); \

#define PUSH_LINE(name) \
    int size = blockSize(instr, 0); \
    int count = 0; \
    while (count < size) { \
        name.push_back(instr.front()); \
        POP_FRONT(instr); \
        count++; \
    }

// constructor with the vector of string input
GameParser::GameParser(vector <string>& input) {
    string open = input.front();
    name = tokenise(open)[0];
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    string line = "";

    instr = input;
    instr.pop_back();
    POP_FRONT(instr);

    while (!instr.empty()) {
        line = instr.front();
        if (regex_match(line, regex("\\#ROW\\=[0-9]*"))) {
            rows = stoi(findAndReplace(line, "#ROW=", ""));
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#COL\\=[0-9]*"))) {
            cols = stoi(findAndReplace(line, "#COL=", ""));
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#PIECE\\((.*)\\)\\{"))) {
            PUSH_BLOCK(pieceDef, pieceDefs);
            PieceParser pieceParser = PieceParser(name, pieceDef);
            pieceParsers.push_back(pieceParser);
        } else if (regex_match(line, regex("\\#MOVE\\((.*)\\)\\{"))) {
            PUSH_BLOCK(move, moveDefs);
        } else if (line == "#PROMOTION{") {
            PUSH_BLOCK(promotion, promotionDefs);
        } else if (line == "#PREMOVE{") {
            PUSH_BLOCK(preMoveUpdate, preMoveDefs);
            TrackerUpdateParser parser = TrackerUpdateParser(preMoveUpdate);
            preMoveParsers.push_back(parser);
        } else if (line == "#POSTMOVE{") {
            PUSH_BLOCK(postMoveUpdate, postMoveDefs);
            TrackerUpdateParser parser = TrackerUpdateParser(postMoveUpdate);
            postMoveParsers.push_back(parser);
        } else if (line == "#TRACKERS{") {
            PUSH_LINE(trackerDefs);
        } else if (line == "#SETUP{") {
            PUSH_LINE(setup);
        } else if (line == "#WIN{") {
            PUSH_LINE(winConds);
        } else if (line == "#DRAW{") {
            PUSH_LINE(drawConds);
        } else {
            CHECK(true, line, "unrecognised instruction");
        }
    }

    for (vector <string> :: iterator it = trackerDefs.begin() + 1; it != trackerDefs.end() - 1; it++) {
        string current = *it;
        CHECK(!regex_match(current, regex("[A-Z\\_]*\\=(\\-)?[0-9]*")), current, "INCORRECT #TRACKER INSTRUCTION");
        string name = current.substr(0, current.find_first_of("="));
        string value = current.substr(current.find_first_of("=") + 1);
        trackers.push_back(current.substr(0, current.find_first_of("=")));
        trackerValues[name] = value;
    }
    for (vector <vector <string>> :: iterator it = pieceDefs.begin(); it != pieceDefs.end(); it++) {
        vector <string> current = *it;
        string line = current[0];
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        pieces.push_back(tokenise(line)[0]);
    }
    for (vector <vector <string>> :: iterator it = moveDefs.begin(); it != moveDefs.end(); it++) {
        MoveParser parser = MoveParser(name, *it, pieces, trackers);
        moveParsers.push_back(parser);
    }
    for (vector <vector <string>> :: iterator it = promotionDefs.begin(); it != promotionDefs.end(); it++) {
        PromotionParser parser = PromotionParser(*it, pieces, trackers);
        promotionParsers.push_back(parser);
    }
}

// produce the content of the header file in the form of a vector of strings
vector <string> GameParser::headerContent() {
    vector <string> content;
    int indent = 0;

    string className = name + "Game";
    className[0] = toupper(className[0]);

    string def = name + "_" + "GAME_H";
    transform(def.begin(), def.end(), def.begin(), ::toupper);

    string trackerIds = "";
    for (vector <string> :: iterator it = trackers.begin() + 1; it != trackers.end() - 1; it++) {
        if (it != trackers.begin() + 1) {
            trackerIds += ", ";
        }
        trackerIds += *it;
    }
    trackerIds += ", num_TRACKERS";

    W("#ifndef " + def)
    W("#define " + def)
    WN
    W("class " + className + ";")
    WN
    W("#include <vector>")
    W("#include <set>")
    W("#include <string>")
    W("#include \"piece.h\"")
    W("#include \"game.h\"")
    WN
    W("typedef enum {" + trackerIds + "} TrackerId;")
    WN
    W_("class " + className + ": public Game {")
        W_("public:")
            // Constructor with the board and the players
            W(className + "();")
            // Destructor
            W("~" + className + "();")
            // update the moves that a player can make
            W("void updateMoves();")
            // set up the pieces for the board and the players
            W("void setUp();")
            // check if the game is over, set finished to be true if so, return
            // true if a player wins and false if there is a draw, the result is 
            // meaningless unless finished is true
            W("virtual bool checkResults();")
            // try the input move, store the move on the stack so that it can be 
            // reversed
            W("virtual void tryMove(GameMove& move, bool isAux);")
            W("virtual void tryMove(GameMove& move);")
        _WE
        W_("private:")
            if (promotionDefs.size() != 0) {
                // promotions
                W("void promotion();")
            }
            // special moves
            for (vector <MoveParser> :: iterator it = moveParsers.begin(); it != moveParsers.end(); it++) {
                vector <string> functionHeaders = (*it).headerContent();
                increaseIndent(functionHeaders, indent);
                content.insert(content.end(), functionHeaders.begin(), functionHeaders.end());
            }
            // update the trackers before a move
            W("void preMove(GameMove& move);")
            // update the trackers after a move
            W("void postMove(GameMove& move);")
        _WE
    _W("};")
    WN
    W("#endif")
    
    return content; 
}

// produce the content of the implementation cpp file in the form of a vector of strings
std::vector <std::string> GameParser::implContent() {
    vector <string> content;
    int indent = 0;

    string className = name + "Game";
    className[0] = toupper(className[0]);

    W("#include \"" + getFileName() + ".h\"")
    WN
    W("#include <cstddef>")
    W("#include <vector>")
    W("#include <set>")
    W("#include <string>")
    W("#include <cstdlib>")
    W("#include <iostream>")
    W("#include <algorithm>")
    W("#include \"piece.h\"")
    W("#include \"board.h\"")
    W("#include \"square.h\"")
    W("#include \"player.h\"")
    WN
    for (vector <PieceParser> :: iterator it = pieceParsers.begin(); it != pieceParsers.end(); it++) {
        W("#include \"" + it->getFileName() + ".h\"")
    }
    WN
    W("using namespace std;");
    WN

    // Constructor with the board and the players
    W_(className + "::" + className + "(): Game(new Board(" + to_string(rows) + ", " + to_string(cols) +")) {")
    _W("}")
    WN

    // Destructor
    W_(className + "::~" + className + "() {")
    _W("}")
    WN

    // try the input move, store the move on the stack so that it can be 
    // reversed
    W_("void " + className + "::tryMove(GameMove& move, bool isAux) {")
        W("Player *current = getCurrentPlayer();")
        W_("if (!isAux) {")
            W("preMove(move);")
        _W("}")
        W("Game::tryMove(move, isAux);")
        for (vector <string> :: iterator it = pieces.begin(); it != pieces.end(); it++) {
            string current = *it;
            W_("if (move.instr == \"" + current + "\") {")
                current[0] = toupper(current[0]);
                W("Piece *promotion = new " + current + "(move.square, move.piece->getPlayer());")
                W("promote(move.piece, promotion);")
            _W("}")
        }
        W_("if (!isAux) {")
            W("postMove(move);")
            W("Player *opposite = current == white ? black : white;")
            W("inCheck = checkTest(opposite);")
        _W("}")
    _W("}")
    WN

    // try the input move, store the move on the stack so that it can be reversed
    W_("void " + className + "::tryMove(GameMove& move) {")
        W(className + "::tryMove(move, false);")
    _W("}")
    WN

    // update the moves that a player can make
    W_("void " + className + "::updateMoves() {")
        W("moves.clear();")
        W("basicMoves();")

        vector <string> moveFunctions;
        for (vector <MoveParser> :: iterator it = moveParsers.begin(); it != moveParsers.end(); it++) {
            moveFunctions.push_back((*it).functionCall());
        }
        increaseIndent(moveFunctions, indent);
        content.insert(content.end(), moveFunctions.begin(), moveFunctions.end());
        
        W("removeIllegalMoves();")
        if (promotionDefs.size() != 0) {
            W("promotion();")
        }
    _W("}")
    WN

    // set up the pieces for the board and the players
    W_("void " + className + "::setUp() {")
        W("trackers = vector <int>(num_TRACKERS);")
        for (vector <string> :: iterator it = trackers.begin(); it != trackers.end(); it++) {
            W("trackers[" + *it + "] = " + trackerValues[*it] + ";")
        }
        W("trackersStack.push_back(trackers);")
        int setupCount = 0;
        for (vector <string> :: iterator it = setup.begin() + 1; it != setup.end() - 1; it++) {
            vector <string> elements = tokenise(*it);
            CHECK(elements.size() != 4, *it, "WRONG NUMBER OF ARGUMENTS IN SETUP")
            string pPlayer = "black";
            if (elements[0] == "#WHITE") {
                pPlayer = "white";
            }
            string pName = elements[1];
            transform(pName.begin(), pName.end(), pName.begin(), ::tolower);
            pName[0] = toupper(pName[0]);
            string pRow = elements[2];
            string pCol = elements[3];
            W("Piece *piece" + to_string(setupCount) + " = new " + pName 
                    + "(board->getSquare(" + pRow + ", " + pCol + "), " + pPlayer + ");");
            W("board->getSquare(" + pRow + ", " + pCol + ")->setPiece(piece" + to_string(setupCount) + ");")
            W(pPlayer + "->addPiece(piece" + to_string(setupCount) + ");")
            W_("if (piece" + to_string(setupCount) + ".isKing()) {")
                if (elements[0] == "#WHITE") {
                    W("whiteKings.push_back(piece" + to_string(setupCount) + ");")
                } else {
                    W("blackKings.push_back(piece" + to_string(setupCount) + ");")
                }
            _W("}")
            setupCount++;
        }
        W("storeBoardState();")
    _W("}")
    WN

    // check if the game is over, set finished to be true if so, return
    // true if a player wins and false if there is a draw, the result is 
    // meaningless unless finished is true
    W_("bool " + className + "::checkResult() {")
        W("bool winCond = false;")
        for (vector <string> :: iterator it = winConds.begin() + 1; it != winConds.end() - 1; it++) {
            if (*it != "#CHECKMATE" && *it != "#STALEMATE") {
                string current = *it;
                cout << current << "\n";
                findAndReplaceInPlace(current, "#COND", "");
                cout << current << "\n";
                W("winCond = winCond || " + current + ";")
            }
        }
        W_("if (winCond) {")
            W("finished = true;")
            W("return true;")
        _W("}")
        W("bool drawCond = false;")
        for (vector <string> :: iterator it = drawConds.begin() + 1; it != drawConds.end() - 1; it++) {
            if (*it != "#CHECKMATE" && *it != "#STALEMATE") {
                string current = *it;
                findAndReplaceInPlace(current, "#COND", "");
                W("drawCond = drawCond || " + current + ";")
            }
        }
        W_("if (drawCond) {")
            W("finished = true;")
            W("return false;")
        _W("}")
        W("updateMoves();")
        W_("if (moves.empty()) {")
            W("finished = true;")
            W_("if (checkTest(getCurrentPlayer())) {")
                if (count(winConds.begin(), winConds.end(), "#CHECKMATE") != 0) {
                    W("return true;")
                } else {
                    W("return false;")
                }
            _W("}")
            if (count(winConds.begin(), winConds.end(), "#STALEMATE") != 0) {
                W("return true;")
            } else {
                W("return false;")
            }
        _W("}")
    _W("}")
    WN

    // the special moves
    for (vector <MoveParser> :: iterator it = moveParsers.begin(); it != moveParsers.end(); it++) {
        vector <string> functionContent = it->implContent();
        increaseIndent(functionContent, indent);
        content.insert(content.end(), functionContent.begin(), functionContent.end());
        WN
    }

    if (promotionDefs.size() != 0) {
        // update the promotion moves
        W_("void " + className + "::promotion() {")
            W("bool cond = true;")
            W("vector <GameMove> temp;")
            for (vector <PromotionParser> :: iterator it = promotionParsers.begin(); it != promotionParsers.end(); it++) {
                vector <string> functionContent = it->implContent();
                increaseIndent(functionContent, indent);
                content.insert(content.end(), functionContent.begin(), functionContent.end());
                WN
            }
            W_("for (vector <GameMove> :: iterator it = temp.begin(); it != temp.end(); it++) {")
                W("moves.push_back(*it)")
            _W("}")
        _W("}")
        WN
    }

    // update the trackers before a move
    W_("void " + className + "::preMove(GameMove& move) {")
        W("bool cond = true;")
        for (vector <TrackerUpdateParser> :: iterator it = preMoveParsers.begin(); it != preMoveParsers.end(); it++) {
            vector <string> functionContent = it->implContent();
            increaseIndent(functionContent, indent);
            content.insert(content.end(), functionContent.begin(), functionContent.end());
            WN
        }
        W("trackersStack.push_back(trackers);")
    _W("}")
    WN

    // update the trackers after a move
    W_("void " + className + "::postMove(GameMove& move) {")
        W("bool cond = true;")
        for (vector <TrackerUpdateParser> :: iterator it = postMoveParsers.begin(); it != postMoveParsers.end(); it++) {
            vector <string> functionContent = it->implContent();
            increaseIndent(functionContent, indent);
            content.insert(content.end(), functionContent.begin(), functionContent.end());
            WN
        }
        W("trackersStack.back() = trackers;")
    _W("}")
    WN
    /*
    for (vector <string> :: iterator it = content.begin(); it != content.end(); it++) {
        cout << *it << "\n";
    }
    */

    // correctly parse the trackers
    for (vector <string> :: iterator it = content.begin(); it != content.end(); it++) {
        for (vector <string> :: iterator tracker = trackers.begin(); tracker != trackers.end(); tracker++) {
            string find = "$" + *tracker + "$";
            string replace = "trackers[" + *tracker + "]";
            findAndReplaceInPlace(*it, find, replace);
        }
    }

    return content;
}

// get the name that the file should have without extension
string GameParser::getFileName() {
    return name + "game";
}