#ifndef CP_KNIGHT_H
#define CP_KNIGHT_H

#include "piece.h"

class Knight;

class Knight: public Piece {
    public:
        // Constructor of a knight at a specific Square belonging to a player
        Knight(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets();
};

#endif