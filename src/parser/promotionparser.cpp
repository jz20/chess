#include "promotionparser.h"

#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>
#include "parserutils.h"

using namespace std;

#define CHECK(cond, error, msg) \
    if (cond) { \
        cout << "incorrect #PROMOTION definition: \n"; \
        cout << msg << "\n"; \
        throw error; \
    }

// could move back to main code, leaving it here for now because it could be useful for #MIRROR
#define PARSE_PROMOTION(colour) \
    W_("if (getCurrentPlayer().getColour == " + colour + ") {") \
        W("cond = true;") \
        for (vector <string> :: iterator it = conds.begin(); it != conds.end(); it++) { \
            W("cond = cond && " + processCond(*it) + ";") \
        } \
        for (vector <vector <string>> :: iterator it = orConds.begin(); it != orConds.end(); it++) { \
            W("cond = cond && " + processOrCond(*it) + ";") \
        } \
        W("cond = cond && " + parseCandidateCheck() + ";") \
        W_("if (cond) {") \
            int count = 0; \
            for (vector <string> :: iterator it = targets.begin(); it != targets.end(); it++) { \
                W("GameMove promotion" + to_string(count) + " = GameMove(move);") \
                W("promotion" + to_string(count) + ".instr = \"" + *it + "\";") \
                W("temp.push_back(promotion);") \
                count++; \
            } \
            W("moves.erase(it);") \
            W("it--;") \
        _W("}") \
    _W("}")

// the constructor with the input
PromotionParser::PromotionParser(vector <string>& input, 
        vector <string>& pieces, vector <string>& trackers) {
    this->pieces = pieces;
    this->trackers = trackers;
    
    promotionPlayer = MIRROR_PROMOTION;
    instr = input;
    instr.pop_back();
    POP_FRONT(instr);

    string line = "";
    while (!instr.empty()) {
        line = instr.front();
        if (line == "#MIRROR") {
            promotionPlayer = MIRROR_PROMOTION;
            POP_FRONT(instr);
        } else if (line == "#WHITE") {
            promotionPlayer = WHITE_PROMOTION;
            POP_FRONT(instr);
        } else if (line == "#BLACK") {
            promotionPlayer = BLACK_PROMOTION;
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#CANDIDATE\\((.*)\\)"))) {
            candidates.push_back(line);
            POP_FRONT(instr);
        } else if (regex_match(line, regex("\\#TARGET\\((.*)\\)"))) {
            targets.push_back(line);
            POP_FRONT(instr);
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
            CHECK(true, line, line);
        }
    }
    CHECK(promotionPlayer == MIRROR_PROMOTION, "OPERATION NOT SUPPORTED", "MIRROR OPERATION NOT SUPPORTED");
}

// produce the content of the implementation cpp file in the form of a vector of strings
/*
    This piece of code needs to be in an iterator for loop
    The following needs to be defined:
        bool cond;
        vector <GameMove> temp;
    */
vector <string> PromotionParser::implContent() {
    vector <string> content;
    int indent = 0;
    if (promotionPlayer == MIRROR_PROMOTION) {
        // not implemented
    } else if (promotionPlayer == WHITE_PROMOTION) {
        PARSE_PROMOTION("WHITE")
    } else if (promotionPlayer == BLACK_PROMOTION) {
        PARSE_PROMOTION("BLACK")
    }
    return content;
}

// process a condition
string PromotionParser::processCond(const string& cond) {
    string result = cond;

    result = findAndReplace(result, "#COND", "");
    result = findAndReplace(result, "#ROWOF", "move.square->getRow()");
    result = findAndReplace(result, "#COLOF", "move.square->getCol()");

    result = replaceKeywords(result);

    return "(" + result + ")";
}
        
// process an or-condition
string PromotionParser::processOrCond(vector <string>& orCond) {
    string result;
    for (vector <string> :: iterator it = orCond.begin() + 1; it != orCond.end() - 1; it++) {
        if (it != orCond.begin() + 1) {
            result += " || ";
        }
        result += processCond(*it);
    }
    return "(" + result + ")";
}

// parse candidate check
string PromotionParser::parseCandidateCheck() {
    CHECK(candidates.size() == 0, candidates, "NO CANDIDATES");
    string result = "";
    string current;
    for (vector <string> :: iterator it = candidates.begin(); it != candidates.end(); it++) {
        current = *it;
        if (it != candidates.begin()) {
            result += " || ";
        }
        current = tokenise(current)[0];
        CHECK((count(pieces.begin(), pieces.end(), current) == 0), current, "PIECE NOT FOUND");
        result += "(move.piece->getName() == \"" + current + "\")";
    }
    return "(" + result + ")";
}