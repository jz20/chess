#include "parsertestrunner.h"

#include "parserutilstest.h"
#include "pieceparsertest.h"
#include "moveparsertest.h"
#include "trackerupdateparsertest.h"
#include "gameparsertest.h"
#include "runnerparsertest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runParserUtilsTests() && result;
    result = runPieceParserTests() && result;
    result = runMoveParserTests() && result;
    result = runTrackerUpdateParserTests() && result;
    result = runGameParserTests() && result;
    result = runRunnerParserTests() && result;
    return result;
}

// main function calling the test runner
int main() {
    return !testRunner();
}