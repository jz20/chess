#ifndef CP_BISHOP_H
#define CP_BISHOP_H

#include "piece.h"

class Bishop;

#include <list>
#include "square.h"

class Bishop: public Piece {
    public:
        void updateMoves();
};

#endif