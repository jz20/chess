#ifndef CP_BISHOP_H
#define CP_BISHOP_H

#include "piece.h"

class Bishop;

class Bishop: public Piece {
    public:
        void updateMoves();
};

#endif