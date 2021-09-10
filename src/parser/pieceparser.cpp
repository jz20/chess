#include "pieceparser.h"

#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>
#include <cctype>
#include <cstddef>
#include "parserutils.h"

using namespace std;

#define CHECK(cond, error, msg) \
    if (cond) { \
        cout << "incorrect #PIECE definition\n"; \
        cout << msg << "\n"; \
        throw error; \
    }

// requires string current to be defined
#define PARSE_MOVEMENT(map, coefficient) \
    for (vector <string> :: iterator it = movement.begin(); it != movement.end(); it++) { \
        current = *it; \
        if (map.count(current) != 0) { \
            W(map[current] + "(&targets);") \
        } else if (regex_match(current, regex("^\\(\\-?[0-9]*\\,\\-?[0-9]*\\)(.*)"))) { \
            vector <string> coordinates = tokenise(current, '(', ')', ','); \
            string functionName = "targetSquare"; \
            if (current.find("*C*") != string::npos) { \
                functionName = "targetCaptureSquare"; \
            } else if (current.find("*NC*") != string::npos) { \
                functionName = "targetNonCaptureSquare"; \
            } \
            int rowOffset = stoi(coordinates[0]); \
            W(functionName + "(&targets, " + to_string(coefficient * rowOffset) + ", " + coordinates[1] + ");") \
        } else { \
            cout << current << "\n"; \
            CHECK(true, movement, "INCORRECT PIECE MOVEMENT") \
        } \
    }

// Constructor with the game name and the input vector of string
PieceParser::PieceParser(const std::string& gameName, const std::vector <std::string>& input) {
    this->gameName = gameName;
    string open = input.front();
    string close = input.back();
    CHECK(!regex_match(open, regex("\\#PIECE\\([A-Za-z]*\\,[A-Za-z]\\)\\{")), open, open);

    this->movement = input;
    POP_FRONT(movement)
    movement.pop_back();
    this->king = false;
    for (vector <string> :: iterator it = movement.begin(); it != movement.end(); it++) {
        if (*it == "#KING") {
            movement.erase(it);
            this->king = true;
        }
    }

    vector <string> info = tokenise(open, '(', ')', ',');
    size_t expectedSize = 2;
    CHECK(info.size() != expectedSize, open, "INCORRECT SQUARE COORDINATE");
    name = info[0];
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    CHECK(name == "game", name, "nameing the piece \"game\" will cause name clashes")
    symbol = info[1][0];

    setUpMoveMapWhite();
    setUpMoveMapBlack();
}

// produce the content of the header file in the form of a vector of strings
vector <string> PieceParser::headerContent() {
    vector <string> content;
    int indent = 0;

    string def = gameName + "_" + name + "_H";
    transform(def.begin(), def.end(), def.begin(), ::toupper); // GAMENAME_NAME_H

    string className = name;
    className[0] = toupper(className[0]); // Name

    W("#ifndef " + def)
    W("#define " + def)
    WN
    W("#include \"piece.h\"")
    W("#include \"square.h\"")
    W("#include \"player.h\"")
    WN
    W("class " + className + ";")
    WN
    W_("class " + className + ": public Piece {")
        W_("public:")
            W(className + "(Square *square, Player *player);")
            W("void updateTargets();")
        _WE
    _W("};")
    WN
    W("#endif")

    return content;
}

// produce the content of the implementation cpp file in the form of a vector of strings
vector <string> PieceParser::implContent() {
    vector <string> content;
    int indent = 0;

    string headerName = getFileName() + ".h";

    string className = name;
    className[0] = toupper(className[0]); // Name

    W("#include \"" + headerName + "\"");
    WN
    W("#include \"piece.h\"")
    W("#include \"square.h\"")
    W("#include \"player.h\"")
    W("#include <vector>")
    W("#include <string>")
    WN
    W_(className + "::" + className + "(Square *square, Player *player): Piece(square, player) {")
        W("name = \"" + name + "\";")
        W_("if (player && player->getColour() == WHITE) {")
            W("symbol = '" + string(1, tolower(symbol)) + "';")
        _W_("} else {")
            W("symbol = '" + string(1, toupper(symbol)) + "';")
        _W("}")
        if (king) {
            W("asKing = true;")
        }
    _W("}")
    WN
    W_("void " + className + "::updateTargets() {")
        W("targets.clear();")
        W_("if (player && player->getColour() == WHITE) {")
            string current = "";
            PARSE_MOVEMENT(moveMapWhite, 1)
        _W_("} else {")
            PARSE_MOVEMENT(moveMapBlack, -1)
        _W("}")

    _W("}");
    return content;
}

// get the file name according to gamename and name
string PieceParser::getFileName() {
    return gameName + name;
}

// set up the moveMap for WHITE
void PieceParser::setUpMoveMapWhite() {
    moveMapWhite["UP"] = "upCol";
    moveMapWhite["DOWN"] = "downCol";
    moveMapWhite["LEFT"] = "leftRow";
    moveMapWhite["RIGHT"] = "rightRow";
    moveMapWhite["UP_LEFT"] = "upLeftDiag";
    moveMapWhite["UP_RIGHT"] = "upRightDiag";
    moveMapWhite["DOWN_LEFT"] = "downLeftDiag";
    moveMapWhite["DOWN_RIGHT"] = "downRightDiag";
}

// set up the moveMapBlack for BLACK
void PieceParser::setUpMoveMapBlack() {
    moveMapBlack["UP"] = "downCol";
    moveMapBlack["DOWN"] = "upCol";
    moveMapBlack["LEFT"] = "leftRow";
    moveMapBlack["RIGHT"] = "rightRow";
    moveMapBlack["UP_LEFT"] = "downLeftDiag";
    moveMapBlack["UP_RIGHT"] = "downRightDiag";
    moveMapBlack["DOWN_LEFT"] = "upLeftDiag";
    moveMapBlack["DOWN_RIGHT"] = "upRightDiag";
}