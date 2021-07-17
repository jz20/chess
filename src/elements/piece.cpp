#include "piece.h"

#include <list>
#include <cstddef>
#include "square.h"

using namespace std;


// Constructor of a piece
Piece::Piece() {
    this->square = NULL;
}

// Constructor of a piece at a specific Square
Piece::Piece(Square *square) {
    Piece();
    this->square = square;
}

// get the square
Square *Piece::getSquare() {
    return square;
}

// set the square
void Piece::setSquare(Square *square) {
    this->square = square;
}

// get the legal moves
list <Square *> Piece::getMoves() {
    return moves;
}