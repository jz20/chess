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
    while (i >= 0 && j >= 0 && board->getSquare(i, j)->isEmpty) {
        // moves + getSquare(i, j);
    }
}