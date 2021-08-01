#ifndef CP_BISHOP_H
#define CP_BISHOP_H

#include "piece.h"

class Bishop;

class Bishop: public Piece {
    public:
        // Constructor of a bishop at a specific Square belonging to a player
        Bishop(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets();
};

#endif