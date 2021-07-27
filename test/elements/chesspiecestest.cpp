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

#define EXPECT(x, y) expected.push_back(board->getSquare(x, y))

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
    Board *board = new Board(8, 8);
    Bishop *bishop = new Bishop(board->getSquare(3, 5), NULL);
    bishop->updateMoves();
    vector <Square *> actual = bishop->getMoves();
    vector <Square *> expected;
    EXPECT(2, 4);
    EXPECT(2, 6);
    EXPECT(4, 4);
    EXPECT(4, 6);
    EXPECT(1, 3);
    EXPECT(1, 7);
    EXPECT(5, 3);
    EXPECT(5, 7);
    EXPECT(0, 2);
    EXPECT(6, 2);
    EXPECT(7, 1);
    bool result = vectorCompare(&actual, &expected);
    delete board;
    delete bishop;
    return result;
}

// test that the knight has the correct squares as legal moves on an empty board
bool testKnightEmpty() {
    Board *board = new Board(8, 8);
    Knight *knight = new Knight(board->getSquare(2, 1), NULL);
    knight->updateMoves();
    vector <Square *> actual = knight->getMoves();
    vector <Square *> expected;
    EXPECT(0, 0);
    EXPECT(0, 2);
    EXPECT(1, 3);
    EXPECT(3, 3);
    EXPECT(4, 0);
    EXPECT(4, 2);
    bool result = vectorCompare(&actual, &expected);
    delete board;
    delete knight;
    return result;
}

// test that the rook has the correct squares as legal moves on an empty board
bool testRookEmpty() {
    Board *board = new Board(8, 8);
    Rook *rook = new Rook(board->getSquare(3, 6), NULL);
    rook->updateMoves();
    vector <Square *> actual = rook->getMoves();
    vector <Square *> expected;
    EXPECT(3, 0);
    EXPECT(3, 1);
    EXPECT(3, 2);
    EXPECT(3, 3);
    EXPECT(3, 4);
    EXPECT(3, 5);
    EXPECT(3, 7);
    EXPECT(0, 6);
    EXPECT(1, 6);
    EXPECT(2, 6);
    EXPECT(4, 6);
    EXPECT(5, 6);
    EXPECT(6, 6);
    EXPECT(7, 6);
    bool result = vectorCompare(&actual, &expected);
    delete board;
    delete rook;
    return result;
}

// test that the queen has the correct squares as legal moves on an empty board
bool testQueenEmpty() {
    Board *board = new Board(8, 8);
    Queen *queen = new Queen(board->getSquare(2, 4), NULL);
    queen->updateMoves();
    vector <Square *> actual = queen->getMoves();
    vector <Square *> expected;
    // rook-like moves
    EXPECT(2, 0);
    EXPECT(2, 1);
    EXPECT(2, 2);
    EXPECT(2, 3);
    EXPECT(2, 5);
    EXPECT(2, 6);
    EXPECT(2, 7);
    EXPECT(0, 4);
    EXPECT(1, 4);
    EXPECT(3, 4);
    EXPECT(4, 4);
    EXPECT(5, 4);
    EXPECT(6, 4);
    EXPECT(7, 4);
    // bishop-like moves
    EXPECT(0, 2);
    EXPECT(1, 3);
    EXPECT(3, 3);
    EXPECT(4, 2);
    EXPECT(5, 1);
    EXPECT(6, 0);
    EXPECT(0, 6);
    EXPECT(1, 5);
    EXPECT(3, 5);
    EXPECT(4, 6);
    EXPECT(5, 7);
    bool result = vectorCompare(&actual, &expected);
    delete board;
    delete queen;
    return result;
}

// test that the king has the correct squares as legal moves on an empty board
bool testKingEmpty() {
    Board *board = new Board(8, 8);
    King *king = new King(board->getSquare(6, 5), NULL);
    king->updateMoves();
    vector <Square *> actual = king->getMoves();
    vector <Square *> expected;
    EXPECT(7, 4);
    EXPECT(7, 5);
    EXPECT(7, 6);
    EXPECT(6, 4);
    EXPECT(6, 6);
    EXPECT(5, 4);
    EXPECT(5, 5);
    EXPECT(5, 6);
    bool result = vectorCompare(&actual, &expected);
    delete board;
    delete king;
    return result;
}

// test that the pawn has the correct squares as legal moves on an empty board
bool testPawnEmpty() {
    Board *board = new Board(8, 8);
    Player *white = new Player(WHITE);
    Player *black = new Player(BLACK);
    Pawn *pawnW = new Pawn(board->getSquare(5, 6), white);
    pawnW->updateMoves();
    vector <Square *> actual = pawnW->getMoves();
    vector <Square *> expected;
    EXPECT(6, 6);
    bool result = vectorCompare(&actual, &expected);
    board->getSquare(5, 6)->setEmpty();
    expected.clear();
    Pawn *pawnB = new Pawn(board->getSquare(6, 5), black);
    EXPECT(5, 5);
    delete board;
    delete pawnW;
    delete pawnB;
    delete white;
    delete black;
    return result;
}

// compare the elements of two vectors of squares disregarding the order,
// returning true if so
bool vectorCompare(vector <Square *> *v1, vector <Square *> *v2) {
    if (v1->size() != v2->size()) {
        return false;
    }
    bool found;
    Square *sq1;
    Square *sq2;
    for (vector <Square *> :: iterator it1 = v1->begin(); it1 != v1->end(); ++it1) {
        found = false;
        for (vector <Square *> :: iterator it2 = v2->begin(); it2 != v2->end() && !found; ++it2) {
            sq1 = *it1;
            sq2 = *it2;
            if (sq1 == sq2) {
                found = true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runChessPiecesTests() {
    cout << "Chess Pieces Test:\n";
    bool result = true;
    TEST(testCreation, "creation");
    TEST(testPlacement, "placement");
    TEST(testBishopEmpty, "bishop - empty board");
    TEST(testKnightEmpty, "knight - empty board");
    TEST(testRookEmpty, "rook - empty board");
    TEST(testQueenEmpty, "queen - empty board");
    TEST(testKingEmpty, "king - empty board");
    TEST(testPawnEmpty, "pawn - empty board");
    return result;
}
