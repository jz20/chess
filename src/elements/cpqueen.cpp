#include "cpqueen.h"

#include <vector>

// update the possible squares for a piece to move to
void Queen::updateMoves() {
    moves.clear();
    // straight line moves
    upCol(&moves);
    downCol(&moves);
    leftRow(&moves);
    rightRow(&moves);
    // diagonal moves
    upLeftDiag(&moves);
    upRightDiag(&moves);
    downLeftDiag(&moves);
    downRightDiag(&moves);
}