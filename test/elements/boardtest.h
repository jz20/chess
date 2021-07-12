#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#include "board.h" // from corresponding source
#include "testutil.h" // from ..

// test the creation of an empty board
bool testEmpty();

// run the unit tests and output the results
bool runBoardTests();

#endif