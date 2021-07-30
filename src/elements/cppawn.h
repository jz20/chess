#ifndef CP_PAWN_H
#define CP_PAWN_H

#include "piece.h"

class Pawn;

class Pawn: public Piece {
    public:
        // Constructor of a pawn at a specific Square belonging to a player
        Pawn(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets();
};

#endif