#include "elementstestrunner.h"
#include "squaretest.h"
#include "boardtest.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runSquareTests() && result;
    result = runBoardTests() && result;
    return result;
}

int main() {
    return !testRunner();
}