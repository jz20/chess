#include "cpbishop.h"

#include <vector>

// update the possible squares for a piece to move to
void Bishop::updateTargets() {
    targets.clear();
    upLeftDiag(&targets);
    upRightDiag(&targets);
    downLeftDiag(&targets);
    downRightDiag(&targets);
}