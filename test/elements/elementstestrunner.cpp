#include "elementstestrunner.h"

// run the unit tests for elements
bool testRunner() {
    bool result = true;
    result = runSquareTests() && result;
    result = runBoardTests() && result;
    std::cout << result;
    return result;
}

int main() {
    return !testRunner();
}