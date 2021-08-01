#include "board.h"
#include "square.h"
#include "piece.h"
#include <iostream>
#include <sstream>

using namespace std;

// constructor of a board with specified rows and cols
Board::Board(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->squares = new Square **[rows];
    for (int i = 0; i < rows; i++) {
        squares[i] = new Square *[cols];
        for (int j = 0; j < cols; j++) {
            squares[i][j] = new Square(i, j, this);
        }
    }
}

// destructor of a board
Board::~Board() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete squares[i][j];
        }
        delete [] squares[i];
    }
    delete [] squares;
}

// returns the square at specified row and col position
Square *Board::getSquare(int row, int col) const {
    return squares[row][col];
}

// get the number of rows
int Board::getRows() const {
    return rows;
}

// get the number of columns
int Board::getCols() const {
    return cols;
}

/*
+-+-+-+-+-+-+-+-+
| | | | | | | | | 
*/


// returning a string representing the board layout
string Board::layout() {
    Square *current = NULL;
    string rep = "";
    stringstream auxStrm;
    for (int i = 0; i < getCols(); i++) {
        rep += "+-";
    }
    rep += "+\n";
    for (int i = getRows() - 1; i >= 0; i--) {
        for (int j = 0; j < getCols(); j++) {
            current = getSquare(i, j);
            rep += "|";
            if (current->isEmpty()) {
                rep += " ";
            } else {
                cout << 2 << "\n";
                auxStrm << *(current->getPiece());
                rep += auxStrm.str();
                cout << 3 << "\n";
            }
        }
        rep += "|\n";
    }
    for (int i = 0; i < getCols(); i++) {
        rep += "+-";
    }
    rep += "+\n";
    return rep;
}

// to String
ostream& operator<<(ostream &strm, const Board &board) {
    Square *current = NULL;
    string rep = "";
    stringstream auxStrm;
    for (int i = 0; i < board.getCols(); i++) {
        rep += "+-";
    }
    rep += "+\n";
    for (int i = board.getRows() - 1; i >= 0; i--) {
        for (int j = 0; j < board.getCols(); j++) {
            current = board.getSquare(i, j);
            rep += "|";
            if (current->isEmpty()) {
                rep += " ";
            } else {    
                auxStrm << *(current->getPiece());
                rep += auxStrm.str();
                auxStrm.str(string());
            }
        }
        rep += "|\n";
    }
    for (int i = 0; i < board.getCols(); i++) {
        rep += "+-";
    }
    rep += "+\n";
    return strm << rep;
}
