#include "cpbishop.h"

#include <list>
#include "square.h"

void Bishop::updateMoves() {
    int row = square->getRow();
    int col = square->getCol();
    Board *board = square->getBoard();
    int rowLimit = board->getRows();
    int colLimit = board->getCols();
    int i;
    int j;
    // bottom left diagonal
    i = row - 1;
    j = col - 1;
    while (i >= 0 && j >= 0 && board->getSquare(i, j)->isEmpty()) {
        moves.push_back(board->getSquare(i, j));
        i--;
        j--;
    }
    // top left diagonal
    i = row + 1;
    j = col - 1;
    while (i < rowLimit && j >= 0 && board->getSquare(i, j)->isEmpty()) {
        moves.push_back(board->getSquare(i, j));
        i++;
        j--;
    }
    // bottom right diagonal
    i = row - 1;
    j = col + 1;
    while (i >= 0 && j < colLimit && board->getSquare(i, j)->isEmpty()) {
        moves.push_back(board->getSquare(i, j));
        i--;
        j++;
    }
    // top right diagonal
    i = row + 1;
    j = col + 1;
    while (i < rowLimit && j < colLimit && board->getSquare(i, j)->isEmpty()) {
        moves.push_back(board->getSquare(i, j));
        i++;
        j++;
    }
}