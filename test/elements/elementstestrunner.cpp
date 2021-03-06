#include "elementstestrunner.h"

#include "squaretest.h"
#include "boardtest.h"
#include "chesspiecestest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runSquareTests() && result;
    result = runBoardTests() && result;
    result = runChessPiecesTests() && result;
    return result;
}

// main function calling the test runner
int main() {
    return !testRunner();
}