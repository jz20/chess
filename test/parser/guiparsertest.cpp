#include "guiparsertest.h"

#include "guiparser.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>
#include <vector>
#include "parserutils.h"

using namespace std;

// test the header is created correctly
bool guiHeaderTest() {
    vector <string> runnerContent = readFile("test_examples/paths.txt");
    GUIParser p("bar", runnerContent);
    writeFile("test_examples/runner.h", p.headerContent());
    cout << "\tfor details check test_examples/runner.h: ";
    return true;
}

// test the cpp implementation is created correctly
bool guiImplTest() {
    vector <string> runnerContent = readFile("test_examples/paths.txt");
    GUIParser p("bar", runnerContent);
    writeFile("test_examples/runner.cpp", p.implContent());
    cout << "\tfor details check test_examples/runner.cpp: ";
    return true;
}

// run the tests and output the results
bool runGUIParserTests() {
    cout << "Runner Parser Test: \n";
    bool result = true;
    TEST(guiHeaderTest, "header")
    TEST(guiImplTest, "implementation file")
    return result;
}