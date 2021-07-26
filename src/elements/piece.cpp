#include "piece.h"

#include <vector>
#include <cstddef>
#include "square.h"
#include "player.h"
#include "board.h"

using namespace std;

// Constructor of a piece belonging to a Player at a specific Square
Piece::Piece(Square *square, Player *player) {
    this->square = square;
    this->player = player;
    this->asKing = false;
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
vector <Square *> Piece::getMoves() {
    return moves;
}

// get the player
Player *Piece::getPlayer() {
    return player;
}

// return whether the piece functions as a king
bool Piece::isAsKing() {
    return asKing;
}

/*
    The following are auxiliary function that help find the moves and add them
    to the moves list
*/

void Piece::upLeftDiag(list <Square *> *moves) {
    int i = square->getRow() + 1;
    int j = square->getCol() - 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i < square->getBoard()->getRows() && j >= 0 && flag) {
        if (board->getSquare(i, j)->isEmpty()) {
            moves->push_back(board->getSquare(i, j));
        } else {
            if (board->getSquare(i, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, j));
            }
            flag = false;
        }
        i++;
        j--;
    }
}

void Piece::downLeftDiag(list <Square *> *moves) {
    int i = square->getRow() - 1;
    int j = square->getCol() - 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i >= 0 && j >= 0 && flag) {
        if (board->getSquare(i, j)->isEmpty()) {
            moves->push_back(board->getSquare(i, j));
        } else {
            if (board->getSquare(i, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, j));
            }
            flag = false;
        }
        i--;
        j--;
    }
}

void Piece::upRightDiag(list <Square *> *moves) {
    int i = square->getRow() + 1;
    int j = square->getCol() + 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i < square->getBoard()->getRows() && j < square->getBoard()->getCols() && flag) {
        if (board->getSquare(i, j)->isEmpty()) {
            moves->push_back(board->getSquare(i, j));
        } else {
            if (board->getSquare(i, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, j));
            }
            flag = false;
        }
        i++;
        j++;
    }
}

void Piece::downRightDiag(list <Square *> *moves) {
    int i = square->getRow() - 1;
    int j = square->getCol() + 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i >= 0 && j < square->getBoard()->getCols() && flag) {
        if (board->getSquare(i, j)->isEmpty()) {
            moves->push_back(board->getSquare(i, j));
        } else {
            if (board->getSquare(i, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, j));
            }
            flag = false;
        }
        i--;
        j++;
    }
}

void Piece::upCol(list <Square *> *moves) {
    int col = square->getCol();
    int i = square->getRow() + 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i < square->getBoard()->getRows() && flag) {
        if (board->getSquare(i, col)->isEmpty()) {
            moves->push_back(board->getSquare(i, col));
        } else {
            if (board->getSquare(i, col)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, col));
            }
            flag = false;
        }
        i++;
    }
}

void Piece::downCol(list <Square *> *moves) {
    int col = square->getCol();
    int i = square->getRow() - 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (i >= 0 && flag) {
        if (board->getSquare(i, col)->isEmpty()) {
            moves->push_back(board->getSquare(i, col));
        } else {
            if (board->getSquare(i, col)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(i, col));
            }
            flag = false;
        }
        i--;
    }
}

void Piece::leftRow(list <Square *> *moves) {
    int row = square->getRow();
    int j = square->getCol() - 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (j >= 0 && flag) {
        if (board->getSquare(row, j)->isEmpty()) {
            moves->push_back(board->getSquare(row, j));
        } else {
            if (board->getSquare(row, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(row, j));
            }
            flag = false;
        }
        j--;
    }
}

void Piece::rightRow(list <Square *> *moves) {
    int row = square->getRow();
    int j = square->getCol() + 1;
    bool flag = true;
    Board *board = square->getBoard();
    while (j < square->getBoard()->getCols() && flag) {
        if (board->getSquare(row, j)->isEmpty()) {
            moves->push_back(board->getSquare(row, j));
        } else {
            if (board->getSquare(row, j)->getPiece()->getPlayer() != player) {
                moves->push_back(board->getSquare(row, j));
            }
            flag = false;
        }
        j++;
    }
}

void Piece::targetSquare(std::list <Square *> *moves, int rowOffset, int colOffset) {
    int row = square->getRow() + rowOffset;
    int col = square->getCol() + colOffset;
    Board *board = square->getBoard();
    int rowLimit = board->getRows();
    int colLimit = board->getCols();
    if (row  >= 0 && row < rowLimit && col >= 0 && col < colLimit
            && (board->getSquare(row, col)->isEmpty() 
            || board->getSquare(row, col)->getPiece()->getPlayer() != player)) {
        moves->push_back(board->getSquare(row, col));
    }
}

// the piece can only move to the target if it causes a capture
void Piece::targetCaptureSquare(std::list <Square *> *moves, int rowOffset, int colOffset) {
    int row = square->getRow() + rowOffset;
    int col = square->getCol() + colOffset;
    Board *board = square->getBoard();
    int rowLimit = board->getRows();
    int colLimit = board->getCols();
    if (row  >= 0 && row < rowLimit && col >= 0 && col < colLimit
            && (!(board->getSquare(row, col)->isEmpty()) 
            && board->getSquare(row, col)->getPiece()->getPlayer() != player)) {
        moves->push_back(board->getSquare(row, col));
    }
}
        
// the piece can only move to the target if it does not cause a capture
void Piece::targetNonCaptureSquare(std::list <Square *> *moves, int rowOffset, int colOffset) {
    int row = square->getRow() + rowOffset;
    int col = square->getCol() + colOffset;
    Board *board = square->getBoard();
    int rowLimit = board->getRows();
    int colLimit = board->getCols();
    if (row  >= 0 && row < rowLimit && col >= 0 && col < colLimit
            && board->getSquare(row, col)->isEmpty()) {
        moves->push_back(board->getSquare(row, col));
    }
}
        