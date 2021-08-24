#include "pieceparsertest.h"

#include "pieceparser.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>
#include <vector>
#include "parserutils.h"

using namespace std;

// test the header is created correctly
bool pieceHeaderTest() {
    vector <string> pieceContent = readFile("test_examples/pieceexample.txt");
    PieceParser p("bar", pieceContent);
    writeFile("test_examples/barfoo.h", p.headerContent());
    cout << "\tfor details check test_examples/barfoo.h: ";
    return true;
}

// test the cpp implementation is created correctly
bool pieceImplTest() {
    vector <string> pieceContent = readFile("test_examples/pieceexample.txt");
    PieceParser p("bar", pieceContent);
    writeFile("test_examples/barfoo.cpp", p.implContent());
    cout << "\tfor details check test_examples/barfoo.cpp: ";
    return true;
}

// run the tests and output the results
bool runPieceParserTests() {
    cout << "Piece Parser Test: \n";
    bool result = true;
    TEST(pieceHeaderTest, "header")
    TEST(pieceImplTest, "implementation file")
    return result;
}