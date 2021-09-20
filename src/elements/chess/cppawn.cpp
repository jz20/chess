#include "cppawn.h"

#include <vector>
#include <string>
#include "board.h"
#include "player.h"

// Constructor of a pawn at a specific Square belonging to a player
Pawn::Pawn(Square *square, Player *player): Piece(square, player) {
    name = "pawn";
    if (player && player->getColour() == WHITE) {
        symbol = 'p';
    } else {
        symbol = 'P';
    }
}

// update the possible squares for a piece to move to
void Pawn::updateTargets(bool ownPieces) {
    targets.clear();
    if (player && (player->getColour() == WHITE)) {
        targetNonCaptureSquare(&targets, 1, 0);
        targetCaptureSquare(&targets, 1, 1, ownPieces);
        targetCaptureSquare(&targets, 1, -1, ownPieces);
    } else {
        targetNonCaptureSquare(&targets, -1, 0);
        targetCaptureSquare(&targets, -1, 1, ownPieces);
        targetCaptureSquare(&targets, -1, -1, ownPieces);
    }
    
}