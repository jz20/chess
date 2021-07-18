#include "chesspiecestest.h"
#include "piece.h" // from corresponding source
#include "testutil.h" // from ..

#include <cstddef>
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
    //delete knight;
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
    board->free();
    delete board;
    //delete bishop;
    return true;
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
