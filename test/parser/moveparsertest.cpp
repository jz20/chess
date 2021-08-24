#include "moveparsertest.h"

#include "moveparser.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>
#include <vector>
#include "parserutils.h"

using namespace std;

// test the header is created correctly
bool moveHeaderTest() {
    vector <string> moveContent = readFile("test_examples/moveexample.txt");
    vector <string> baz;
    MoveParser p("bar", moveContent, baz, baz);
    writeFile("test_examples/moveheader.txt", p.headerContent());
    cout << "\tfor details check test_examples/moveheader.txt: ";
    return true;
}

// test the cpp implementation is created correctly
bool moveImplTest() {
    vector <string> moveContent = readFile("test_examples/moveexample.txt");
    vector <string> baz;
    MoveParser p("bar", moveContent, baz, baz);
    writeFile("test_examples/moveimpl.txt", p.implContent());
    cout << "\tfor details check test_examples/moveimpl.txt: ";
    return true;
}

// run the tests and output the results
bool runMoveParserTests() {
    cout << "Move Parser Test: \n";
    bool result = true;
    TEST(moveHeaderTest, "header")
    TEST(moveImplTest, "implementation file")
    return result;
}