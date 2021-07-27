#include "cppawn.h"

#include <vector>
#include "board.h"
#include "player.h"

// update the possible squares for a piece to move to
void Pawn::updateMoves() {
    if (player && (player->getColour() == WHITE)) {
        targetNonCaptureSquare(&moves, 1, 0);
        targetCaptureSquare(&moves, 1, 1);
        targetCaptureSquare(&moves, 1, -1);
    } else {
        targetNonCaptureSquare(&moves, -1, 0);
        targetCaptureSquare(&moves, -1, 1);
        targetCaptureSquare(&moves, -1, -1);
    }
    
}