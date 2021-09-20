#ifndef CP_QUEEN_H
#define CP_QUEEN_H

#include "piece.h"

class Queen;

class Queen: public Piece {
    public:
        // Constructor of a queen at a specific Square belonging to a player
        Queen(Square *square, Player *player);
        // update the possible squares for a piece to move to
        void updateTargets(bool ownPieces = false);
};

#endif