#include "cpbishop.h"

#include <list>

void Bishop::updateMoves() {
    upLeftDiag(&moves);
    upRightDiag(&moves);
    downLeftDiag(&moves);
    downRightDiag(&moves);
}