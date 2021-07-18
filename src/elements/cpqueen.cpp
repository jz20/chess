#include "cpqueen.h"

#include <list>

void Queen::updateMoves() {
    // straight line moves
    upCol(&moves);
    downCol(&moves);
    leftRow(&moves);
    rightRow(&moves);
    // diagonal moves
    upLeftDiag(&moves);
    upRightDiag(&moves);
    downLeftDiag(&moves);
    downRightDiag(&moves);
}