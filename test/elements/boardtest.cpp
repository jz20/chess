#include "boardtest.h"

using namespace std;

// in each unit test true signals success

// test the creation of an empty board
bool testEmpty() {
    Board *board = new Board(0, 0);
    board->free();
    delete board;
    return true;
}

// test the creation of an 3 by 15 board
bool test3x15() {
    Board *board = new Board(3, 15);
    board->free();
    delete board;
    return true;
}

// test that the squares in the board are correctly labelled
bool testSquareLabels() {
    const int rows = 8;
    const int cols = 8;
    Board *board = new Board(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board->getSquare(i, j)->getRow() != i 
                    || board->getSquare(i, j)->getCol() != j) {
                return false;   
            }
        }
    }
    board->free();
    delete board;
    return true;
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runBoardTests() {
    cout << "Board Test:\n";
    bool result = true;
    TEST(testEmpty, "empty board");
    TEST(test3x15, "3 by 15");
    TEST(testSquareLabels, "square labels");
    return result;
}