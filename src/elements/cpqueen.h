#ifndef CP_QUEEN_H
#define CP_QUEEN_H

#include "piece.h"

class Queen;

class Queen: public Piece {
    public:
        void updateMoves();
};

#endif