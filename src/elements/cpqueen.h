#ifndef CP_QUEEN_H
#define CP_QUEEN_H

#include "piece.h"

class Queen;

class Queen: public Piece {
    using Piece::Piece;
    public:
        // update the possible squares for a piece to move to
        void updateMoves();
};

#endif