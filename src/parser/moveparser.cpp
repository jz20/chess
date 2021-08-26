#include "moveparser.h"

#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include "parserutils.h"

using namespace std;

#define CHECK(cond, error, msg) \
    if (cond) { \
        cout << "incorrect #MOVE definition\n"; \
        cout << msg << "\n"; \
        throw error; \
    }

#define EACH_PIECE(name) \
    if (eachPiece) { \
        name = findAndReplace(name, "#ROWOF", "piece->getSquare()->getRow()"); \
        name = findAndReplace(name, "#COLOF", "piece->getSquare()->getCol()"); \
    }

#define PROCESS_MOVE \
    W("bool cond = true;"); \
    string cond; \
    for (vector <string> :: iterator it = conds.begin(); it != conds.end(); it++) { \
        W("cond = cond && " + processCond(*it) + ";"); \
    } \
    for (vector <vector <string>> :: iterator it = orConds.begin(); it != orConds.end(); it++) { \
        W("cond = cond && " + processOrCond(*it) + ";"); \
    } \
    W_("if (cond) {"); \
        W("GameMove move;"); \
        W("move.piece = " + origin + ".getPiece();"); \
        W("move.square = " + destination + ";"); \
        W("move.instr = " + name + ";"); \
        W("moves.push_back(move);"); \
        vector <string> current; \
        int count = 0; \
        W("GameMove *parent = &move;"); \
        for (vector <vector <string>> :: iterator it = auxMoves.begin(); it != auxMoves.end(); it++) { \
            current = *it; \
            string auxOrigin = ""; \
            string auxDestination = ""; \
            W("GameMove *aux" + to_string(count) + " = new GameMove;"); \
            bool flag0 = false; \
            bool flag1 = false; \
            for (vector <string> :: iterator it1 = current.begin(); it1 != current.end(); it1++) { \
                if (regex_match(*it1, regex("\\#ORIGIN\\((.*)\\)"))) { \
                    auxOrigin = *it1; \
                    processOrigin(auxOrigin); \
                    if (auxOrigin.find("#NONE") != string::npos) { \
                        W("aux" + to_string(count) + "->piece = NULL;"); \
                    } else { \
                        W("aux" + to_string(count) + "->piece = " + auxOrigin + ".getPiece();"); \
                    } \
                    flag0 = true; \
                } else if (regex_match(*it1, regex("\\#DESTINATION\\((.*)\\)"))) { \
                    auxDestination = *it1; \
                    processDestination(auxDestination); \
                    W("aux" + to_string(count) + "->square = " + auxDestination + ";"); \
                    flag1 = true; \
                } \
            } \
            CHECK(!(flag0 && flag1), current, "INCORRECT #AUXMOVE"); \
            W("parent->aux->reset(aux" + to_string(count) + "));"); \
            W("parent = aux" + to_string(count) + ";"); \
            count++; \
        } \
    _W("}");

// the constructor with the input
MoveParser::MoveParser(const string gName, vector <string>& input, 
        vector <string>& pieces, vector <string>& trackers) {
    this->gameName = gName;
    gameName[0] = toupper(gameName[0]);
    this->pieces = pieces;
    this->trackers = trackers;

    string open = input.front();
    string close = input.back();
    CHECK(!regex_match(open, regex("\\#MOVE\\([A-Za-z]*\\)\\{")), open, "UNSUPPORTED NAME");

    name = tokenise(open)[0];

    this->instr = input;
    POP_FRONT(instr);
    instr.pop_back();

    movePlayer = MIRROR_MOVE;
    eachPiece = false;
    pieceName = "";
    string line = "";
    while (!instr.empty()) {
        line = instr.front();
        if (line == "#MIRROR") {
            movePlayer = MIRROR_MOVE;
            POP_FRONT(instr);
        } else if (line == "#WHITE") {
            movePlayer = WHITE_MOVE;
            POP_FRONT(instr);
        } else if (line == "#BLACK") {
            movePlayer = BLACK_MOVE;
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#EACHPIECE\\([A-Za-z]*\\)"))) {
            eachPiece = true;
            pieceName = tokenise(line)[0];
            transform(pieceName.begin(), pieceName.end(), pieceName.begin(), ::tolower);
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#ORIGIN\\((.*)\\)"))) {
            origin = line;
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#DESTINATION\\((.*)\\)"))) {
            destination = line;
            POP_FRONT(instr);
        } else if (line == "#AUXMOVE{") {
            int size = blockSize(instr, 0);
            vector <string> aux;
            int count = 0;
            while (count < size) {
                aux.push_back(instr.front());
                POP_FRONT(instr);
                count++;
            }
            auxMoves.push_back(aux);
        } else if (regex_match(line, regex("\\#COND\\((.*)\\)"))) {
            conds.push_back(line);
            POP_FRONT(instr);
        } else if (line == "#ORCOND{") {
            int size = blockSize(instr, 0);
            vector <string> orCond;
            int count = 0;
            while (count < size) {
                orCond.push_back(instr.front());
                POP_FRONT(instr);
                count++;
            }
            orConds.push_back(orCond);
        } else {
            cout << line << "\n";
            CHECK(true, line, line);
        }
    }
    CHECK(movePlayer == MIRROR_MOVE, "OPERATION NOT SUPPORTED", "MIRROR OPERATION NOT SUPPORTED");


    processOrigin(origin);
    processDestination(destination);
}

vector <string> MoveParser::headerContent() {
    vector <string> content;
    int indent = 0;
    W("void " + name + "();");
    return content;
}

// produce the content of the implementation cpp file in the form of a vector of strings
vector <string> MoveParser::implContent() {
    vector <string> content;
    int indent = 0;
    W_("void " + gameName + "::" + name + "() {");
    W("Player *current = getCurrentPlayer();");
    if (movePlayer == MIRROR_MOVE) {
        /*
        W_("if (current->getColour() == WHITE) {");
        W("Piece *piece = NULL;");
        if (eachPiece) {
            W_("for (vector <Piece *> :: iterator it = current.getPieces().begin(); it != current.getPieces().end(); it ++) {");
                W("piece = *it;");
                W_("if (piece.getName() == " + pieceName + ") {");
                    PROCESS_MOVE;
                _W("}");
            _W("}");
        } else {
            PROCESS_MOVE;
        }
        _W_("} else {");
            W_("if (current->getColour() == BLACK) {");
            W("Piece *piece = NULL;");
            if (eachPiece) {
                W_("for (vector <Piece *> :: iterator it = current.getPieces().begin(); it != current.getPieces().end(); it ++) {");
                    W("piece = *it;");
                    W_("if (piece.getName() == " + pieceName + ") {");
                        PROCESS_MOVE;
                    _W("}");
                _W("}");
            } else {
                PROCESS_MOVE;
            }
        _W("}");
        */
    } else if (movePlayer == WHITE_MOVE) {
        W_("if (current->getColour() == WHITE) {");
        if (eachPiece) {
            W("Piece *piece = NULL;");
            W_("for (vector <Piece *> :: iterator it = current.getPieces().begin(); it != current.getPieces().end(); it ++) {");
                W("piece = *it;");
                W_("if (piece.getName() == " + pieceName + ") {");
                    PROCESS_MOVE;
                _W("}");
            _W("}");
        } else {
            PROCESS_MOVE;
        }
        _W("}");
    } else if (movePlayer == BLACK_MOVE) {
        W_("if (current->getColour() == BLACK) {");
        W("Piece *piece = NULL;");
        if (eachPiece) {
            W("Piece *piece = NULL;");
            W_("for (vector <Piece *> :: iterator it = current.getPieces().begin(); it != current.getPieces().end(); it ++) {");
                W("piece = *it;");
                W_("if (piece.getName() == " + pieceName + ") {");
                    PROCESS_MOVE;
                _W("}");
            _W("}");
        } else {
            PROCESS_MOVE;
        }
        _W("}");
    }
    _W("}");
    return content;
}

// function call: the line to call this move to be processed
string MoveParser::functionCall() {
    return name + "();";
}

// process the origin
void MoveParser::processOrigin(std::string& ori) {
    ori = findAndReplace(ori, "#ORIGIN", "game->getBoard()->getSquare");
    EACH_PIECE(ori);
}

// process the destination
void MoveParser::processDestination(std::string& des) {
    des = findAndReplace(des, "#DESTINATION", "game->getBoard()->getSquare");
    EACH_PIECE(des);
}

// process a condition
string MoveParser::processCond(const string& cond) {
    string result = cond;
    EACH_PIECE(result);

    result = findAndReplace(result, "#COND", "");

    result = replaceKeywords(result);

    return "(" + result + ")";
}
        
// process an or-condition
string MoveParser::processOrCond(vector <string>& orCond) {
    string result;
    for (vector <string> :: iterator it = orCond.begin() + 1; it != orCond.end() - 1; it++) {
        if (it != orCond.begin() + 1) {
            result += " || ";
        }
        result += processCond(*it);
    }
    return "(" + result + ")";
}