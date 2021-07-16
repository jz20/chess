#include "board.h"
#include "square.h"
using namespace std;

// constructor of a board with specified rows and cols
Board::Board(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->squares = new Square **[rows];
    for (int i = 0; i < rows; i++) {
        squares[i] = new Square *[cols];
        for (int j = 0; j < cols; j++) {
            squares[i][j] = new Square(i, j);
        }
    }
}

// returns the square at specified row and col position
Square *Board::getSquare(int row, int col) {
    return squares[row][col];
}

// free associated memory allocations
void Board::free() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            squares[i][j]->free();
            delete squares[i][j];
        }
        delete [] squares[i];
    }
    delete [] squares;
}