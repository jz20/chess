#ifndef BOARD_H
#define BOARD_H

class Board;

#include "square.h"
#include <iostream>

class Board {
    public:
        // constructor of a board with specified rows and cols
        Board(int rows, int cols);
        // destructor of a board
        ~Board();
        // returns the square at specified row and col position
        Square *getSquare(int row, int col) const;
        // get the number of rows
        int getRows() const;
        // get the number of columns
        int getCols() const;
        // to String
        friend std::ostream& operator<<(std::ostream &strm, const Board &board);
        // snapshot, other version of toString
        std::string snapshot();
    private:
        int rows;
        int cols;
        Square ***squares;
};

#endif