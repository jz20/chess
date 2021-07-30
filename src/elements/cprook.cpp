#include "cprook.h"

#include <vector>
#include <string>

// Constructor of a rook at a specific Square belonging to a player
Rook::Rook(Square *square, Player *player): Piece(square, player) {
    name = "rook";
}

// update the possible squares for a piece to move to
void Rook::updateTargets() {
    targets.clear();
    upCol(&targets);
    downCol(&targets);
    leftRow(&targets);
    rightRow(&targets);
}