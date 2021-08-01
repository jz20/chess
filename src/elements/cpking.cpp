#include "cpking.h"

#include <vector>
#include <string>

// Constructor of a king at a specific Square belonging to a player
King::King(Square *square, Player *player): Piece(square, player) {
    asKing = true;
    name = "king";
    if (player && player->getColour() == WHITE) {
        symbol = 'k';
    } else {
        symbol = 'K';
    }
}

// update the possible squares for a piece to move to
void King::updateTargets() {
    targets.clear();
    targetSquare(&targets, 1, 0);
    targetSquare(&targets, 0, -1);
    targetSquare(&targets, -1, 0);
    targetSquare(&targets, 0, 1);
    targetSquare(&targets, 1, 1);
    targetSquare(&targets, 1, -1);
    targetSquare(&targets, -1, -1);
    targetSquare(&targets, -1, 1);
}