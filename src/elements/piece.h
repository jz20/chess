#ifndef PIECE_H
#define PIECE_H

class Piece;

#include <list>
#include "square.h"

class Piece {
    public:
        // Constructor of a piece at a specific Square
        Piece(Square *square);
        // Constructor of a piece
        Piece();
        // get the square
        Square *getSquare();
        // set the square
        void setSquare(Square *square);
        // update the legal moves of a piece
        virtual void updateMoves();
        // get the legal moves
        std::list <Square *> getMoves();
    protected:
        Square *square;
        std::list <Square *> moves;
};

#endif