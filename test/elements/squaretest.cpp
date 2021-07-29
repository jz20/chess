#include "squaretest.h"
#include "square.h" // from corresponding source
#include "testutil.h" // from ..

using namespace std;

// in each unit test true signals success

// test the creation of a square
bool testCreate() {
    Square *square = new Square(0, 0);
    delete square;
    return true;
}

// test if the square has the correct row and col values
bool testRowCol() {
    Square *square = new Square(7, 3);
    bool result = false;
    if (square->getRow() == 7 && square->getCol() == 3) {
        result = true;
    }
    delete square;
    return result;
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runSquareTests() {
    cout << "Square Test:\n";
    bool result = true;
    TEST(testCreate, "create");
    TEST(testRowCol, "row col");
    return result;
}