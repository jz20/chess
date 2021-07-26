#include "chesspiecestest.h"
#include "piece.h" // from corresponding source
#include "testutil.h" // from ..

#include <cstddef>
#include <vector>
#include "board.h"
#include "square.h"
#include "player.h"

/*
Chess pieces:
*/
#include "cpking.h"
#include "cpqueen.h"
#include "cprook.h"
#include "cpbishop.h"
#include "cpknight.h"
#include "cppawn.h"

using namespace std;

/*
    This test file includes tests for all the standard chess pieces.
*/


// in each test true signals success

// test that the piece creation is correct (knight)
bool testCreation() {
    Knight *knight = new Knight(NULL, NULL);
    delete knight;
    return true;
}

// test that the piece is correctly place in a Square in a Board (bishop)
bool testPlacement() {
    Board *board = new Board(8, 8);
    Bishop *bishop = new Bishop(NULL, NULL);
    board->getSquare(3, 3)->setPiece(bishop);
    bishop->setSquare(board->getSquare(3, 3));
    if (board->getSquare(3, 3)->getPiece() != bishop) {
        return false;
    }
    delete board;
    delete bishop;
    return true;
}

// test that the bishop has the correct squares as legal moves on an empty board
bool testBishopEmpty() {
    return true;
}

// compare the elements of two vectors of squares disregarding the order,
// returning true if so
bool vectorCompare(std::vector <Square *> v1, std::vector <Square *> v2) {
    bool found;
    for (vector <Square *> :: iterator it1 = v1.begin(); it1 != v1.end(); ++it1) {
        found = false;
        for (vector <Square *> :: iterator it2 = v1.begin(); it2 != v2.end() && !found; ++it2) {
            if (*it1 == *it2) {
                found = true;
                v2.erase(it2);
            }
        }
        if (!found) {
            return false;
        }
    }
    return v2.empty();
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runChessPiecesTests() {
    cout << "Chess Pieces Test:\n";
    bool result = true;
    TEST(testCreation, "creation");
    TEST(testPlacement, "placement");
    return result;
}
