#include "barfoo.h"

#include "piece.h"
#include "square.h"
#include "player.h"
#include <vector>
#include <string>

Foo::Foo(Square *square, Player *player): Piece(square, player) {
	name = "foo";
	if (player && player->getColour() == WHITE) {
		symbol = 'f';
	} else {
		symbol = 'F';
	}
}

void Foo::updateTargets() {
	targets.clear();
	if (player && player->getColour() == WHITE) {
		upLeftDiag(&targets);
		upRightDiag(&targets);
		targetSquare(&targets, 1, 0);
		targetNonCaptureSquare(&targets, -1, 1);
		targetNonCaptureSquare(&targets, -1, -1);
	} else {
		downLeftDiag(&targets);
		downRightDiag(&targets);
		targetSquare(&targets, -1, 0);
		targetNonCaptureSquare(&targets, 1, 1);
		targetNonCaptureSquare(&targets, 1, -1);
	}
}
