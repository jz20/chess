#ifndef BOARD_TEST_H
#define BOARD_TEST_H

// test the creation of an empty board
bool testEmpty();

// test the creation of an 3 by 15 board
bool test3x15();

// test that the squares in the board are correctly labelled
bool testSquareLabels();

// test that the squares in a board has the pointer to this board
bool testSquareBoard();

// run the unit tests and output the results
bool runBoardTests();

#endif