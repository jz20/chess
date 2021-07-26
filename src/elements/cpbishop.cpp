#include "cpbishop.h"

#include <vector>

// update the possible squares for a piece to move to
void Bishop::updateMoves() {
    upLeftDiag(&moves);
    upRightDiag(&moves);
    downLeftDiag(&moves);
    downRightDiag(&moves);
}