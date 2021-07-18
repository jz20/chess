#include "cpknight.h"

#include <list>
#include "board.h"

// update the possible squares for a piece to move to
void Knight::updateMoves() {
    targetSquare(&moves, 2, 3);
    targetSquare(&moves, 3, 2);
    targetSquare(&moves, 3, -2);
    targetSquare(&moves, 2, -3);
    targetSquare(&moves, -2, -3);
    targetSquare(&moves, -3, -2);
    targetSquare(&moves, -3, 2);
    targetSquare(&moves, -2, 3);
}