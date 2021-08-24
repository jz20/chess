#include "parsertestrunner.h"

#include "parserutilstest.h"
#include "pieceparsertest.h"
#include "moveparsertest.h"
#include "trackerupdateparsertest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runParserUtilsTests() && result;
    result = runPieceParserTests() && result;
    result = runMoveParserTests() && result;
    result = runTrackerUpdateParserTests() && result;
    return result;
}

// main function calling the test runner
int main() {
    return !testRunner();
}