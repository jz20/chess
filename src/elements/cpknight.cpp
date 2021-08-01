#include "cpknight.h"

#include <vector>
#include <string>
#include "board.h"

// Constructor of a bishop at a specific Square belonging to a player
Knight::Knight(Square *square, Player *player): Piece(square, player) {
    name = "knight";
    if (player && player->getColour() == WHITE) {
        symbol = 'n';
    } else {
        symbol = 'N';
    }
}

// update the possible squares for a piece to move to
void Knight::updateTargets() {
    targets.clear();
    targetSquare(&targets, 1, 2);
    targetSquare(&targets, 2, 1);
    targetSquare(&targets, 2, -1);
    targetSquare(&targets, 1, -2);
    targetSquare(&targets, -1, -2);
    targetSquare(&targets, -2, -1);
    targetSquare(&targets, -2, 1);
    targetSquare(&targets, -1, 2);
}