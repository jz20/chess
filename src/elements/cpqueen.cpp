#include "cpqueen.h"

#include <vector>
#include <string>

// Constructor of a queen at a specific Square belonging to a player
Queen::Queen(Square *square, Player *player): Piece(square, player) {
    name = "queen";
}

// update the possible squares for a piece to move to
void Queen::updateTargets() {
    targets.clear();
    // straight line targets
    upCol(&targets);
    downCol(&targets);
    leftRow(&targets);
    rightRow(&targets);
    // diagonal targets
    upLeftDiag(&targets);
    upRightDiag(&targets);
    downLeftDiag(&targets);
    downRightDiag(&targets);
}