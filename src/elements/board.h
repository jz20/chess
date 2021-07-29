#ifndef BOARD_H
#define BOARD_H

class Board;

#include "square.h"

class Board {
    public:
        // constructor of a board with specified rows and cols
        Board(int rows, int cols);
        // destructor of a board
        ~Board();
        // returns the square at specified row and col position
        Square *getSquare(int row, int col);
        // get the number of rows
        int getRows();
        // get the number of columns
        int getCols();
    private:
        int rows;
        int cols;
        Square ***squares;
};

#endif