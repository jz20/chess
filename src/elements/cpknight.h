#ifndef CP_KNIGHT_H
#define CP_KNIGHT_H

#include "piece.h"

class Knight;

class Knight: public Piece {
    using Piece::Piece;
    public:
        // update the possible squares for a piece to move to
        void updateMoves();
};

#endif