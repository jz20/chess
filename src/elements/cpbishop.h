#ifndef CP_BISHOP_H
#define CP_BISHOP_H

#include "piece.h"

class Bishop;

class Bishop: public Piece {
    using Piece::Piece;
    public:
        // update the possible squares for a piece to move to
        void updateMoves();
};

#endif