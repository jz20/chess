#include "cpbishop.h"

#include <vector>
#include <string>

// Constructor of a bishop at a specific Square belonging to a player
Bishop::Bishop(Square *square, Player *player): Piece(square, player) {
    name = "bishop";
    if (player && player->getColour() == WHITE) {
        symbol = 'b';
    } else {
        symbol = 'B';
    }
}

// update the possible squares for a piece to move to
void Bishop::updateTargets(bool ownPieces) {
    targets.clear();
    upLeftDiag(&targets, ownPieces);
    upRightDiag(&targets, ownPieces);
    downLeftDiag(&targets, ownPieces);
    downRightDiag(&targets, ownPieces);
}