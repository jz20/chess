#ifndef SQUARE_H
#define SQUARE_H

class Square;

#include "board.h"
#include "piece.h"

class Square {
    public:
        // constructor of a square at specified row and col position
        // in the specified board
        Square(int row, int col, Board *board);
        // constructor of a square at specified row and col position
        Square(int row, int col);
        // return the row postition
        int getRow();
        // return the col position
        int getCol();
        // free associated memory allocations
        void free();
        // set a specific piece at the square
        void setPiece(Piece *piece);
        // mark the square empty
        void setEmpty();
        // return whether the square is empty
        bool isEmpty();
        // get the board
        Board *getBoard();
    private:
        Board *board;
        int row;
        int col;
        Piece *piece;
        bool empty;
};

#endif