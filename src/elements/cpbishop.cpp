#include "cpbishop.h"

#include <vector>
#include <string>

// Constructor of a bishop at a specific Square belonging to a player
Bishop::Bishop(Square *square, Player *player): Piece(square, player) {
    name = "bishop";
}

// update the possible squares for a piece to move to
void Bishop::updateTargets() {
    targets.clear();
    upLeftDiag(&targets);
    upRightDiag(&targets);
    downLeftDiag(&targets);
    downRightDiag(&targets);
}