#include "cprook.h"

#include <vector>

// update the possible squares for a piece to move to
void Rook::updateMoves() {
    upCol(&moves);
    downCol(&moves);
    leftRow(&moves);
    rightRow(&moves);
}