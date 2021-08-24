#include "gameparser.h"

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include "pieceparser.h"
#include "parserutils.h"

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
    while (!instr.empty()) {
        line = instr.front();
        if (regex_match(line, regex("\\#ROW\\=[0-9]*"))) {
            rows = stoi(findAndReplace(line, "#ROW=", ""));
        } else if (regex_match(line, regex("\\#COL\\=[0-9]*"))) {
            rows = stoi(findAndReplace(line, "#COL=", ""));
        } else if (line == "#PIECE{") {
            PUSH_BLOCK(pieceDef, pieceDefs);
            PieceParser pieceParser = PieceParser(name, pieceDef);
            pieceParsers.push_back(pieceParser);
        } else if (line == "#MOVE{") {
            PUSH_BLOCK(move, moves);
        } else if (line == "#PREMOVE{") {
            PUSH_BLOCK(premoveUpdate, premoveUpdates);
        } else if (line == "#POSTMOVE{") {
            PUSH_BLOCK(postmoveUpdate, postmoveUpdates);
        } else if (line == "#TRACKERS{") {
            PUSH_LINE(trackers);
        } else if (line == "#SETUP{") {
            PUSH_LINE(setup);
        } else if (line == "#WIN{") {
            PUSH_LINE(winConds);
        } else if (line == "#DRAW{") {
            PUSH_LINE(drawConds);
        } else {
            cout << line << "\n";
            CHECK(true, line, "unrecognised instruction");
        }
    }
}