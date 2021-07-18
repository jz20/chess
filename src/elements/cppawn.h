#ifndef CP_PAWN_H
#define CP_PAWN_H

#include "piece.h"

class Pawn;

class Pawn: public Piece {
    using Piece::Piece;
    public:
        // update the possible squares for a piece to move to
        void updateMoves();
};

#endif