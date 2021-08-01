#include "square.h"

#include <cstddef>
#include "board.h"
#include "piece.h"

using namespace std;

// constructor of a square at specified row and col position
// in the specified board
Square::Square(int row, int col, Board *board):Square(row, col) {
    this->board = board;
}

// constructor of a square at specified row and col position
Square::Square(int row, int col) {
    this->row = row;
    this->col = col;
    this->piece = NULL;
    this->board = NULL;
}

// return the row postition
int Square::getRow() {
    return this->row;
}

// return the col position
int Square::getCol() {
    return this->col;
}

// set a specific piece at the square
void Square::setPiece(Piece *piece) {
    this->piece = piece;
}

// get the piece
Piece *Square::getPiece() {
    return piece;
}

// mark the square empty
void Square::setEmpty() {
    this->piece = NULL;
}

// return whether the square is empty
bool Square::isEmpty() {
    return piece == NULL;
}

// get the board
Board *Square::getBoard() {
    return board;
}
