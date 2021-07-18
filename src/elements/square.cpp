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
    this->empty = true;
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

// free associated memory allocations
void Square::free() {
    // may need to free something in the future
}

// set a specific piece at the square
void Square::setPiece(Piece *piece) {
    this->piece = piece;
    this->empty = false;
}

// get the piece
Piece *Square::getPiece() {
    return piece;
}

// mark the square empty
void Square::setEmpty() {
    this->empty = true;
}

// return whether the square is empty
bool Square::isEmpty() {
    return empty;
}

// get the board
Board *Square::getBoard() {
    return board;
}
