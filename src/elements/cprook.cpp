#include "cprook.h"

#include <list>

void Rook::updateMoves() {
    upCol(&moves);
    downCol(&moves);
    leftRow(&moves);
    rightRow(&moves);
}