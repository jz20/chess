#ifndef CP_ROOK_H
#define CP_ROOK_H

#include "piece.h"

class Rook;

class Rook: public Piece {
    using Piece::Piece;
    public:
        // update the possible squares for a piece to move to
        void updateMoves();
};

#endif