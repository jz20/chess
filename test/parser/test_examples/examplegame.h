#ifndef PARTIALCHESS_GAME_H
#define PARTIALCHESS_GAME_H

class PartialchessGame;

#include <vector>
#include <set>
#include <string>
#include "piece.h"
#include "game.h"

typedef enum {WSC, WLC, BSC, BLC, EP_COL, FIFTY, REP, num_TRACKERS} TrackerId;

class PartialchessGame: public Game {
	public:
		PartialchessGame();
		~PartialchessGame();
		void updateMoves();
		void setUp();
		virtual bool checkResult();
		virtual void tryMove(GameMove& move, bool isAux);
		virtual void tryMove(GameMove& move);
	private:
		void promotion();
		void wshortcastling();
		void wlongcastling();
		void wpawntwosquares();
		void wenpassant();
		void preMove(GameMove& move);
		void postMove(GameMove& move);
};

#endif
