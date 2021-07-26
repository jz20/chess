#ifndef CHESS_PIECES_TEST_H
#define CHESS_PIECES_TEST_H

#include "square.h"
#include <vector>

// test that the piece creation is correct
bool testCreation();

// test that the piece is correctly place in a Square in a Board
bool testPlacement();

// test that the bishop has the correct squares as legal moves on an empty board
bool testBishopEmpty();

// compare the elements of two vectors of squares disregarding the order,
// returning true if so
bool vectorCompare(std::vector <Square *> v1, std::vector <Square *> v2);

// run the tests and output the results
bool runChessPiecesTests();

#endif