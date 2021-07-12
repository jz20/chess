#ifndef SQUARE_TEST_H
#define SQUARE_TEST_H

#include "square.h" // from corresponding source
#include "testutil.h" // from ..

// test the creation of a square
bool testCreate();

// test if the square has the correct row and col values
bool testRowCol();

// run the unit tests and output the results
bool runSquareTests();

#endif