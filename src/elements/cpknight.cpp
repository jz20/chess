#include "cpknight.h"

#include <vector>
#include "board.h"

// update the possible squares for a piece to move to
void Knight::updateMoves() {
    moves.clear();
    targetSquare(&moves, 1, 2);
    targetSquare(&moves, 2, 1);
    targetSquare(&moves, 2, -1);
    targetSquare(&moves, 1, -2);
    targetSquare(&moves, -1, -2);
    targetSquare(&moves, -2, -1);
    targetSquare(&moves, -2, 1);
    targetSquare(&moves, -1, 2);
}