#include "gameparsertest.h"

#include "gameparser.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>
#include <vector>
#include "parserutils.h"
#include "pieceparser.h"
#include "moveparser.h"
#include "promotionparser.h"
#include "trackerupdateparser.h"

using namespace std;

// test the header is created correctly
bool gameHeaderTest() {
    vector <string> gameContent = readFile("test_examples/gameexample.txt");
    GameParser p(gameContent);
    writeFile("test_examples/examplegame.h", p.headerContent());
    cout << "\tfor details check test_examples/examplegame.h: ";
    return true;
}

// test the cpp implementation is created correctly
bool gameImplTest() {
    vector <string> gameContent = readFile("test_examples/gameexample.txt");
    GameParser p(gameContent);
    writeFile("test_examples/examplegame.cpp", p.implContent());
    cout << "\tfor details check test_examples/examplegame.cpp: ";
    return true;
}

// run the tests and output the results
bool runGameParserTests() {
    cout << "Game Parser Test: \n";
    bool result = true;
    TEST(gameHeaderTest, "header")
    TEST(gameImplTest, "implementation")
    return result;
}