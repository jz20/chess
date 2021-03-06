#include "trackerupdateparser.h"

#include <vector>
#include <string>
#include <regex>
#include "parserutils.h"

using namespace std;

#define REPLACE(name) \
    name = findAndReplace(name, "#ROWOFORIGIN", "move.piece->getSquare()->getRow()"); \
    name = findAndReplace(name, "#COLOFORIGIN", "move.piece->getSquare()->getCol()"); \
    name = findAndReplace(name, "#ROWOFDESTINATION", "move.square->getRow()"); \
    name = findAndReplace(name, "#COLOFDESTINATION", "move.square->getCol()"); \
    name = findAndReplace(name, "#INSTR", "move.instr"); \
    name = findAndReplace(name, "#NAME", "move.piece->name()"); \
    name = findAndReplace(name, "#REPETITION", "getRepetition()"); \

// constructor with the input vector of strings
TrackerUpdateParser::TrackerUpdateParser(std::vector <std::string>& input) {
    instr = input;
    string line = "";
    colour = BOTH;

    for (vector <string> :: iterator it = instr.begin() + 1; it != instr.end() - 1; it++) {
        line = *it;
        if (regex_match(line, regex("\\#COND\\((.*)\\)"))) {
            conds.push_back(line);
            instr.erase(it);
            it--;
        } else if (line == "#ORCOND{") {
            int size = blockSize(instr, it - instr.begin());
            vector <string> orCond;
            int count = 0;
            while (count < size) {
                orCond.push_back(*it);
                instr.erase(it);
                count++;
            }
            it--;
            orConds.push_back(orCond);
            it--;
        } else if (line == "#WHITE") {
            colour = WHITE;
        } else if (line == "#WHITE") {
            colour = BLACK;
        }
    }
}

// produce the content of the implementation cpp file in the form of a vector of strings
/*
requires bool cond to be defined
*/
vector <string> TrackerUpdateParser::implContent() {
    vector <string> content;
    int indent = 0;
    W("cond = true;");
    if (colour == WHITE) {
        W("cond = cond && move.piece->getPlayer()->getColour() == WHITE;");
    } else if (colour == BLACK) {
        W("cond = cond && move.piece->getPlayer()->getColour() == BLACK;");
    }
    for (vector <string> :: iterator it = conds.begin(); it != conds.end(); it++) {
        W("cond = cond && " + processCond(*it) + ";");
    }
    for (vector <vector <string>> :: iterator it = orConds.begin(); it != orConds.end(); it++) {
        W("cond = cond && " + processOrCond(*it) + ";");
    }
    W_("if (cond) {");
        string current;
        for (vector <string> :: iterator it = instr.begin() + 1; it != instr.end() - 1; it++) {
            current = *it;
            REPLACE(current);
            W(current + ";");
        }
    _W("}");
    return content;
}

// process a condition
string TrackerUpdateParser::processCond(const string& cond) {
    string result = cond;
    result = findAndReplace(result, "#COND", "");

    REPLACE(result);

    result = replaceKeywords(result);

    return '(' + result + ')';
}

// process an or-condition
string TrackerUpdateParser::processOrCond(vector <string>& orCond) {
    string result;
    for (vector <string> :: iterator it = orCond.begin() + 1; it != orCond.end() - 1; it++) {
        if (it != orCond.begin() + 1) {
            result += " || ";
        }
        result += processCond(*it);
    }
    return "(" + result + ")";
}