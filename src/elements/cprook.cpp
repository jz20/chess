#include "cprook.h"

#include <vector>

// update the possible squares for a piece to move to
void Rook::updateTargets() {
    targets.clear();
    upCol(&targets);
    downCol(&targets);
    leftRow(&targets);
    rightRow(&targets);
}