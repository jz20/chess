#include "parsertestrunner.h"

#include "parserutilstest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runParserUtilsTests() && result;
    return result;
}

// main function calling the test runner
int main() {
    return !testRunner();
}