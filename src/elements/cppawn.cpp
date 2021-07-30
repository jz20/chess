#include "cppawn.h"

#include <vector>
#include <string>
#include "board.h"
#include "player.h"

// Constructor of a pawn at a specific Square belonging to a player
Pawn::Pawn(Square *square, Player *player): Piece(square, player) {
    name = "pawn";
}

// update the possible squares for a piece to move to
void Pawn::updateTargets() {
    targets.clear();
    if (player && (player->getColour() == WHITE)) {
        targetNonCaptureSquare(&targets, 1, 0);
        targetCaptureSquare(&targets, 1, 1);
        targetCaptureSquare(&targets, 1, -1);
    } else {
        targetNonCaptureSquare(&targets, -1, 0);
        targetCaptureSquare(&targets, -1, 1);
        targetCaptureSquare(&targets, -1, -1);
    }
    
}