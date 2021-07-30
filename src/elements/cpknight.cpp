#include "cpknight.h"

#include <vector>
#include "board.h"

// update the possible squares for a piece to move to
void Knight::updateTargets() {
    targets.clear();
    targetSquare(&targets, 1, 2);
    targetSquare(&targets, 2, 1);
    targetSquare(&targets, 2, -1);
    targetSquare(&targets, 1, -2);
    targetSquare(&targets, -1, -2);
    targetSquare(&targets, -2, -1);
    targetSquare(&targets, -2, 1);
    targetSquare(&targets, -1, 2);
}