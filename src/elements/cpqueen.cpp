#include "cpqueen.h"

#include <vector>

// update the possible squares for a piece to move to
void Queen::updateTargets() {
    targets.clear();
    // straight line targets
    upCol(&targets);
    downCol(&targets);
    leftRow(&targets);
    rightRow(&targets);
    // diagonal targets
    upLeftDiag(&targets);
    upRightDiag(&targets);
    downLeftDiag(&targets);
    downRightDiag(&targets);
}