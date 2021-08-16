#ifndef BAR_FOO_H
#define BAR_FOO_H

#include "piece.h"
#include "square.h"
#include "player.h"

class Foo;

class Foo: public Piece {
	public:
		Foo(Square *square, Player *player);
		void updateTargets();
};

#endif
