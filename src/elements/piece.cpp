#include "piece.h"

#include <list>
#include <cstddef>
#include "square.h"
#include "player.h"

using namespace std;


// Constructor of a piece belonging to a Player
Piece::Piece(Player *player) {
    this->square = NULL;
}

// Constructor of a piece belonging to a Player at a specific Square
Piece::Piece(Square *square, Player *player) {
    this->square = square;
    this->player = player;
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

// get the player
Player *Piece::getPlayer() {
    return player;
}

/*
    The following are auxiliary function that help find the moves and add them
    to the moves list
*/

void Piece::upLeftDiag(std::list <Square *> *moves) {
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

void Piece::downLeftDiag(std::list <Square *> *moves) {
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

void Piece::upRightDiag(std::list <Square *> *moves) {
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

void Piece::downRightDiag(std::list <Square *> *moves) {
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