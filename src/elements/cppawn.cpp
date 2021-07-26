#include "cppawn.h"

#include <vector>
#include "board.h"

// update the possible squares for a piece to move to
void Pawn::updateMoves() {
    targetNonCaptureSquare(&moves, 1, 0);
    targetCaptureSquare(&moves, 1, 1);
    targetCaptureSquare(&moves, 1, -1);
}