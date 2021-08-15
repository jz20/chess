#include "pieceparser.h"

#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>
#include "parserutils.h"

using namespace std;

#define CHECK(cond, error) \
    if (cond) { \
        cout << "incorrect #PIECE definition\n"; \
        throw error; \
    }

// Constructor with the game name and the input vector of string
PieceParser::PieceParser(const std::string& gameName, const std::vector <std::string>& input) {
    this->gameName = gameName;
    string open = input.front();
    string close = input.back();
    CHECK(!regex_match(open, regex("#PIECE\\([A-Za-z]*,[A-Za-z]\\){")), open);
    CHECK(close != "}", close);
    this->movement = input;
    movement.erase(movement.begin());
    movement.pop_back();
    this->king = false;
    for (vector <string> :: iterator it = movement.begin(); it != movement.end(); it++) {
        if (*it == "#KING") {
            movement.erase(it);
            this->king = true;
        }
    }
    vector <string> info = tokenise(open, '(', ')', ',');
    int expectedSize = 2;
    CHECK(info.size() != expectedSize, open);
    name = info[0];
    symbol = info[1];
}

// produce the content of the header file in the form of a vector of strings
vector <string> PieceParser::headerContent() {
    vector <string> content;
    
    // if () {}
    string def = gameName; 
    return content;
}