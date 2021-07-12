#ifndef SQUARE_H
#define SQUARE_H

class Square {
    public:
        // constructor of a square at specified row and col position
        Square(int row, int col);
        // return the row postition
        int getRow();
        // return the col position
        int getCol();
        // free associated memory allocations
        void free();
    private:
        int row;
        int col;
};

#endif