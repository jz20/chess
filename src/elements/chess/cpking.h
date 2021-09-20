#ifndef CP_KING_H
#define CP_KING_H

#include "piece.h"

class King;

class King: public Piece {
    public:
        // Constructor of a king at a specific Square belonging to a player
        King(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets(bool ownPieces = false);
};

#endif