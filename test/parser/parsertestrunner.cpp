#include "parsertestrunner.h"

#include "parserutilstest.h"
#include "pieceparsertest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runParserUtilsTests() && result;
    result = runPieceParserTests() && result;
    return result;
}

// main function calling the test runner
int main() {
    return !testRunner();
}