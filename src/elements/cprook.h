#ifndef CP_ROOK_H
#define CP_ROOK_H

#include "piece.h"

class Rook;

class Rook: public Piece {
    public:
        // Constructor of a rook at a specific Square belonging to a player
        Rook(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets();
};

#endif