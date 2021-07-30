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

#define EXPECT(y, x) expected.push_back(board->getSquare(y, x))

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

// test that the bishop has the correct squares as legal targets on an empty board
bool testBishopEmpty() {
    Board *board = new Board(8, 8);
    Bishop *bishop = new Bishop(board->getSquare(3, 5), NULL);
    bishop->updateTargets();
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

// test that the knight has the correct squares as legal targets on an empty board
bool testKnightEmpty() {
    Board *board = new Board(8, 8);
    Knight *knight = new Knight(board->getSquare(2, 1), NULL);
    knight->updateTargets();
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

// test that the rook has the correct squares as legal targets on an empty board
bool testRookEmpty() {
    Board *board = new Board(8, 8);
    Rook *rook = new Rook(board->getSquare(3, 6), NULL);
    rook->updateTargets();
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

// test that the queen has the correct squares as legal targets on an empty board
bool testQueenEmpty() {
    Board *board = new Board(8, 8);
    Queen *queen = new Queen(board->getSquare(2, 4), NULL);
    queen->updateTargets();
    vector <Square *> actual = queen->getMoves();
    vector <Square *> expected;
    // rook-like targets
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
    // bishop-like targets
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

// test that the king has the correct squares as legal targets on an empty board
bool testKingEmpty() {
    Board *board = new Board(8, 8);
    King *king = new King(board->getSquare(6, 5), NULL);
    king->updateTargets();
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

// test that the pawn has the correct squares as legal targets on an empty board
bool testPawnEmpty() {
    Board *board = new Board(8, 8);
    Player *white = new Player(WHITE);
    Player *black = new Player(BLACK);
    Pawn *pawnW = new Pawn(board->getSquare(5, 6), white);
    pawnW->updateTargets();
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

// test that the pieces has the correct squares as legal targets when interacting
// with other pieces, without considering special rules

/*
     +-+-+-+-+-+-+-+-+
7(8) |R| | | | |K| |R|
6(7) |P|P| | |Q|P|P| |
5(6) | |p|P| | | |N| |
4(5) |p| | | | | | |P|
3(4) | | |n| | | | | |
2(3) | | | |b| | | |p|
1(2) | | |p| | |p|p| |
0(1) | |r| |q|r| |k| |
     +-+-+-+-+-+-+-+-+
      0 1 2 3 4 5 6 7
      a b c d e f g h
*/

#define BPIECE(y, x, name, Type) \
        Piece *name = new Type(board->getSquare(y, x), black); \
        board->getSquare(y, x)->setPiece(name); \
        black->addPiece(name);

#define WPIECE(y, x, name, Type) \
        Piece *name = new Type(board->getSquare(y, x), white); \
        board->getSquare(y, x)->setPiece(name); \
        white->addPiece(name);

#define VERIFY(name) \
        if (!vectorCompare(&actual, &expected)) { \
            cout << "failure at " << name << "\n"; \
            result = false; \
        }   \
        expected.clear();

bool testBoardInteraction() {
    // board setup
    Board *board = new Board(8, 8);
    Player *white = new Player(WHITE);
    Player *black = new Player(BLACK);
    WPIECE(0, 1, wr1, Rook);
    WPIECE(0, 3, wq, Queen);
    WPIECE(0, 4, wr2, Rook);
    WPIECE(0, 6, wk, King);
    WPIECE(1, 2, wp1, Pawn);
    WPIECE(1, 5, wp2, Pawn);
    WPIECE(1, 6, wp3, Pawn);
    WPIECE(2, 3, wb, Bishop);
    WPIECE(2, 7, wp4, Pawn);
    WPIECE(3, 2, wn, Knight);
    WPIECE(4, 0, wp5, Pawn);
    WPIECE(5, 1, wp6, Pawn);
    BPIECE(7, 0, br1, Rook);
    BPIECE(7, 5, bk, King);
    BPIECE(7, 7, br2, Rook);
    BPIECE(6, 0, bp1, Pawn);
    BPIECE(6, 1, bp2, Pawn);
    BPIECE(6, 4, bq, Queen);
    BPIECE(6, 5, bp3, Pawn);
    BPIECE(6, 6, bp4, Pawn);
    BPIECE(5, 2, bp5, Pawn);
    BPIECE(5, 6, bn, Knight);
    BPIECE(4, 7, bp6, Pawn);

    vector <Square *> actual;
    vector <Square *> expected;
    bool result = true;

    // testing the white bishop
    wb->updateTargets();
    actual = wb->getMoves();
    EXPECT(3, 4);
    EXPECT(1, 4);
    EXPECT(4, 5);
    EXPECT(0, 5);
    EXPECT(5, 6);
    VERIFY("white bishop");
    
    // testing the white knight
    wn->updateTargets();
    actual = wn->getMoves();
    EXPECT(2, 0);
    EXPECT(1, 1);
    EXPECT(1, 3);
    EXPECT(2, 4);
    EXPECT(4, 4);
    EXPECT(5, 3);
    VERIFY("white knight");

    // testing the white b pawn
    wp6->updateTargets();
    actual = wp6->getMoves();
    EXPECT(6, 0);
    VERIFY("white b pawn");
    
    // testing the black queen
    bq->updateTargets();
    actual = bq->getMoves();
    EXPECT(0, 4);
    EXPECT(1, 4);
    EXPECT(2, 4);
    EXPECT(3, 4);
    EXPECT(4, 4);
    EXPECT(5, 4);
    EXPECT(7, 4);
    EXPECT(6, 2);
    EXPECT(6, 3);
    EXPECT(7, 3);
    EXPECT(5, 3);
    EXPECT(4, 2);
    EXPECT(3, 1);
    EXPECT(2, 0);
    EXPECT(5, 5);
    EXPECT(4, 6);
    EXPECT(3, 7);
    VERIFY("black queen");

    // testing the black h rook
    br2->updateTargets();
    actual = br2->getMoves();
    EXPECT(7, 6);
    EXPECT(6, 7);
    EXPECT(5, 7);
    VERIFY("black h rook");

    // testing the black king
    bk->updateTargets();
    actual = bk->getMoves();
    EXPECT(7, 6);
    EXPECT(7, 4);
    VERIFY("black king");

    delete board;
    delete black;
    delete white;
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
    TEST(testBoardInteraction, "board interaction");
    return result;
}
