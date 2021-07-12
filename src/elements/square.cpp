#include "square.h"
using namespace std;

// constructor of a square at specified row and col position
Square::Square(int row, int col) {
    this->row = row;
    this->col = col;
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
