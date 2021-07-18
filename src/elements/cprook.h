#ifndef CP_ROOK_H
#define CP_ROOK_H

#include "piece.h"

class Rook;

class Rook: public Piece {
    public:
        void updateMoves();
};

#endif