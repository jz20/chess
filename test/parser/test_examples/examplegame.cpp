#include "partialchessgame.h"

#include <cstddef>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "piece.h"
#include "board.h"
#include "square.h"
#include "player.h"

#include "partialchessqueen.h"
#include "partialchessrook.h"
#include "partialchessbishop.h"
#include "partialchessknight.h"
#include "partialchesspawn.h"
#include "partialchessking.h"

using namespace std;

PartialchessGame::PartialchessGame(): Game(new Board(8, 8)) {
}

PartialchessGame::~PartialchessGame() {
}

void PartialchessGame::tryMove(GameMove& move, bool isAux) {
	Player *current = getCurrentPlayer();
	if (!isAux) {
		preMove(move);
	}
	Game::tryMove(move, isAux);
	if (move.instr == "queen") {
		Piece *promotion = new Queen(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (move.instr == "rook") {
		Piece *promotion = new Rook(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (move.instr == "bishop") {
		Piece *promotion = new Bishop(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (move.instr == "knight") {
		Piece *promotion = new Knight(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (move.instr == "pawn") {
		Piece *promotion = new Pawn(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (move.instr == "king") {
		Piece *promotion = new King(move.square, move.piece->getPlayer());
		promote(move.piece, promotion);
	}
	if (!isAux) {
		postMove(move);
		Player *opposite = current == white ? black : white;
		inCheck = checkTest(opposite);
	}
}

void PartialchessGame::tryMove(GameMove& move) {
	PartialchessGame::tryMove(move, false);
}

void PartialchessGame::updateMoves() {
	moves.clear();
	basicMoves();
	wshortcastling();
	wlongcastling();
	wpawntwosquares();
	wenpassant();
	removeIllegalMoves();
	promotion();
}

void PartialchessGame::setUp() {
	trackers = vector <int>(num_TRACKERS);
	trackers[WSC] = 1;
	trackers[WLC] = 1;
	trackers[BSC] = 1;
	trackers[BLC] = 1;
	trackers[EP_COL] = -1;
	trackers[FIFTY] = 0;
	trackers[REP] = 0;
	trackersStack.push_back(trackers);
	Piece *piece0 = new Rook(board->getSquare(0, 0), white);
	board->getSquare(0, 0)->setPiece(piece0);
	white->addPiece(piece0);
	if (piece0->isAsKing()) {
		whiteKings.push_back(piece0);
	}
	Piece *piece1 = new Knight(board->getSquare(0, 1), white);
	board->getSquare(0, 1)->setPiece(piece1);
	white->addPiece(piece1);
	if (piece1->isAsKing()) {
		whiteKings.push_back(piece1);
	}
	Piece *piece2 = new Bishop(board->getSquare(0, 2), white);
	board->getSquare(0, 2)->setPiece(piece2);
	white->addPiece(piece2);
	if (piece2->isAsKing()) {
		whiteKings.push_back(piece2);
	}
	Piece *piece3 = new Queen(board->getSquare(0, 3), white);
	board->getSquare(0, 3)->setPiece(piece3);
	white->addPiece(piece3);
	if (piece3->isAsKing()) {
		whiteKings.push_back(piece3);
	}
	Piece *piece4 = new King(board->getSquare(0, 4), white);
	board->getSquare(0, 4)->setPiece(piece4);
	white->addPiece(piece4);
	if (piece4->isAsKing()) {
		whiteKings.push_back(piece4);
	}
	Piece *piece5 = new Bishop(board->getSquare(0, 5), white);
	board->getSquare(0, 5)->setPiece(piece5);
	white->addPiece(piece5);
	if (piece5->isAsKing()) {
		whiteKings.push_back(piece5);
	}
	Piece *piece6 = new Knight(board->getSquare(0, 6), white);
	board->getSquare(0, 6)->setPiece(piece6);
	white->addPiece(piece6);
	if (piece6->isAsKing()) {
		whiteKings.push_back(piece6);
	}
	Piece *piece7 = new Rook(board->getSquare(0, 7), white);
	board->getSquare(0, 7)->setPiece(piece7);
	white->addPiece(piece7);
	if (piece7->isAsKing()) {
		whiteKings.push_back(piece7);
	}
	Piece *piece8 = new Pawn(board->getSquare(1, 0), white);
	board->getSquare(1, 0)->setPiece(piece8);
	white->addPiece(piece8);
	if (piece8->isAsKing()) {
		whiteKings.push_back(piece8);
	}
	Piece *piece9 = new Pawn(board->getSquare(1, 1), white);
	board->getSquare(1, 1)->setPiece(piece9);
	white->addPiece(piece9);
	if (piece9->isAsKing()) {
		whiteKings.push_back(piece9);
	}
	Piece *piece10 = new Pawn(board->getSquare(1, 2), white);
	board->getSquare(1, 2)->setPiece(piece10);
	white->addPiece(piece10);
	if (piece10->isAsKing()) {
		whiteKings.push_back(piece10);
	}
	Piece *piece11 = new Pawn(board->getSquare(1, 3), white);
	board->getSquare(1, 3)->setPiece(piece11);
	white->addPiece(piece11);
	if (piece11->isAsKing()) {
		whiteKings.push_back(piece11);
	}
	Piece *piece12 = new Pawn(board->getSquare(1, 4), white);
	board->getSquare(1, 4)->setPiece(piece12);
	white->addPiece(piece12);
	if (piece12->isAsKing()) {
		whiteKings.push_back(piece12);
	}
	Piece *piece13 = new Pawn(board->getSquare(1, 5), white);
	board->getSquare(1, 5)->setPiece(piece13);
	white->addPiece(piece13);
	if (piece13->isAsKing()) {
		whiteKings.push_back(piece13);
	}
	Piece *piece14 = new Pawn(board->getSquare(1, 6), white);
	board->getSquare(1, 6)->setPiece(piece14);
	white->addPiece(piece14);
	if (piece14->isAsKing()) {
		whiteKings.push_back(piece14);
	}
	Piece *piece15 = new Pawn(board->getSquare(1, 7), white);
	board->getSquare(1, 7)->setPiece(piece15);
	white->addPiece(piece15);
	if (piece15->isAsKing()) {
		whiteKings.push_back(piece15);
	}
	Piece *piece16 = new Rook(board->getSquare(0, 0), black);
	board->getSquare(0, 0)->setPiece(piece16);
	black->addPiece(piece16);
	if (piece16->isAsKing()) {
		blackKings.push_back(piece16);
	}
	Piece *piece17 = new Knight(board->getSquare(7, 1), black);
	board->getSquare(7, 1)->setPiece(piece17);
	black->addPiece(piece17);
	if (piece17->isAsKing()) {
		blackKings.push_back(piece17);
	}
	Piece *piece18 = new Bishop(board->getSquare(7, 2), black);
	board->getSquare(7, 2)->setPiece(piece18);
	black->addPiece(piece18);
	if (piece18->isAsKing()) {
		blackKings.push_back(piece18);
	}
	Piece *piece19 = new Queen(board->getSquare(7, 3), black);
	board->getSquare(7, 3)->setPiece(piece19);
	black->addPiece(piece19);
	if (piece19->isAsKing()) {
		blackKings.push_back(piece19);
	}
	Piece *piece20 = new King(board->getSquare(7, 4), black);
	board->getSquare(7, 4)->setPiece(piece20);
	black->addPiece(piece20);
	if (piece20->isAsKing()) {
		blackKings.push_back(piece20);
	}
	Piece *piece21 = new Bishop(board->getSquare(7, 5), black);
	board->getSquare(7, 5)->setPiece(piece21);
	black->addPiece(piece21);
	if (piece21->isAsKing()) {
		blackKings.push_back(piece21);
	}
	Piece *piece22 = new Knight(board->getSquare(7, 6), black);
	board->getSquare(7, 6)->setPiece(piece22);
	black->addPiece(piece22);
	if (piece22->isAsKing()) {
		blackKings.push_back(piece22);
	}
	Piece *piece23 = new Rook(board->getSquare(6, 7), black);
	board->getSquare(6, 7)->setPiece(piece23);
	black->addPiece(piece23);
	if (piece23->isAsKing()) {
		blackKings.push_back(piece23);
	}
	Piece *piece24 = new Pawn(board->getSquare(6, 0), black);
	board->getSquare(6, 0)->setPiece(piece24);
	black->addPiece(piece24);
	if (piece24->isAsKing()) {
		blackKings.push_back(piece24);
	}
	Piece *piece25 = new Pawn(board->getSquare(6, 1), black);
	board->getSquare(6, 1)->setPiece(piece25);
	black->addPiece(piece25);
	if (piece25->isAsKing()) {
		blackKings.push_back(piece25);
	}
	Piece *piece26 = new Pawn(board->getSquare(6, 2), black);
	board->getSquare(6, 2)->setPiece(piece26);
	black->addPiece(piece26);
	if (piece26->isAsKing()) {
		blackKings.push_back(piece26);
	}
	Piece *piece27 = new Pawn(board->getSquare(6, 3), black);
	board->getSquare(6, 3)->setPiece(piece27);
	black->addPiece(piece27);
	if (piece27->isAsKing()) {
		blackKings.push_back(piece27);
	}
	Piece *piece28 = new Pawn(board->getSquare(6, 4), black);
	board->getSquare(6, 4)->setPiece(piece28);
	black->addPiece(piece28);
	if (piece28->isAsKing()) {
		blackKings.push_back(piece28);
	}
	Piece *piece29 = new Pawn(board->getSquare(6, 5), black);
	board->getSquare(6, 5)->setPiece(piece29);
	black->addPiece(piece29);
	if (piece29->isAsKing()) {
		blackKings.push_back(piece29);
	}
	Piece *piece30 = new Pawn(board->getSquare(6, 6), black);
	board->getSquare(6, 6)->setPiece(piece30);
	black->addPiece(piece30);
	if (piece30->isAsKing()) {
		blackKings.push_back(piece30);
	}
	Piece *piece31 = new Pawn(board->getSquare(6, 7), black);
	board->getSquare(6, 7)->setPiece(piece31);
	black->addPiece(piece31);
	if (piece31->isAsKing()) {
		blackKings.push_back(piece31);
	}
	storeBoardState();
}

bool PartialchessGame::checkResult() {
	bool winCond = false;
	if (winCond) {
		finished = true;
		return true;
	}
	bool drawCond = false;
	drawCond = drawCond || (trackers[REP]>=3);
	drawCond = drawCond || (trackers[FIFTY]/2>=50);
	if (drawCond) {
		finished = true;
		return false;
	}
	updateMoves();
	if (moves.empty()) {
		finished = true;
		if (checkTest(getCurrentPlayer())) {
			return true;
		}
		return false;
	}
	return false;
}

void PartialchessGame::wshortcastling() {
	Player *current = getCurrentPlayer();
	if (current->getColour() == WHITE) {
		bool cond = true;
		cond = cond && ((trackers[WSC]==1,trackers[BSC]==1));
		cond = cond && ((getBoard()->getSquare(0,5))->isEmpty());
		cond = cond && ((getBoard()->getSquare(0,6))->isEmpty());
		cond = cond && (squaresControlled(getOppositePlayer()).count((getBoard()->getSquare(0,5))) == 0);
		cond = cond && (squaresControlled(getOppositePlayer()).count((getBoard()->getSquare(0,6))) == 0);
		if (cond) {
			GameMove move;
			move.piece = getBoard()->getSquare(0,4)->getPiece();
			move.square = getBoard()->getSquare(0,6);
			move.instr = "wshortcastling";
			moves.push_back(move);
			GameMove *parent = &move;
			GameMove *aux0 = new GameMove;
			aux0->piece = getBoard()->getSquare(0,7)->getPiece();
			aux0->square = getBoard()->getSquare(0,5);
			parent->aux.reset(aux0);
			parent = aux0;
		}
	}
}

void PartialchessGame::wlongcastling() {
	Player *current = getCurrentPlayer();
	if (current->getColour() == WHITE) {
		bool cond = true;
		cond = cond && ((trackers[WLC]==1));
		cond = cond && ((getBoard()->getSquare(0,2))->isEmpty());
		cond = cond && ((getBoard()->getSquare(0,3))->isEmpty());
		cond = cond && (squaresControlled(getOppositePlayer()).count((getBoard()->getSquare(0,2))) == 0);
		cond = cond && (squaresControlled(getOppositePlayer()).count((getBoard()->getSquare(0,3))) == 0);
		if (cond) {
			GameMove move;
			move.piece = getBoard()->getSquare(0,4)->getPiece();
			move.square = getBoard()->getSquare(0,2);
			move.instr = "wlongcastling";
			moves.push_back(move);
			GameMove *parent = &move;
			GameMove *aux0 = new GameMove;
			aux0->piece = getBoard()->getSquare(0,0)->getPiece();
			aux0->square = getBoard()->getSquare(0,3);
			parent->aux.reset(aux0);
			parent = aux0;
		}
	}
}

void PartialchessGame::wpawntwosquares() {
	Player *current = getCurrentPlayer();
	if (current->getColour() == WHITE) {
		Piece *piece = NULL;
		for (vector <Piece *> :: iterator it = current->getPieces().begin(); it != current->getPieces().end(); it ++) {
			piece = *it;
			if (piece->getName() == "pawn") {
				bool cond = true;
				cond = cond && ((piece->getSquare()->getRow()==$1));
				cond = cond && ((getBoard()->getSquare($2,piece->getSquare()->getCol()))->isEmpty());
				cond = cond && ((getBoard()->getSquare($3,piece->getSquare()->getCol()))->isEmpty());
				if (cond) {
					GameMove move;
					move.piece = getBoard()->getSquare($1,piece->getSquare()->getCol())->getPiece();
					move.square = getBoard()->getSquare($3,piece->getSquare()->getCol());
					move.instr = "wpawntwosquares";
					moves.push_back(move);
					GameMove *parent = &move;
				}
			}
		}
	}
}

void PartialchessGame::wenpassant() {
	Player *current = getCurrentPlayer();
	if (current->getColour() == WHITE) {
		Piece *piece = NULL;
		for (vector <Piece *> :: iterator it = current->getPieces().begin(); it != current->getPieces().end(); it ++) {
			piece = *it;
			if (piece->getName() == "pawn") {
				bool cond = true;
				cond = cond && ((trackers[EP_COL]!=-1));
				cond = cond && ((piece->getSquare()->getRow()==4));
				cond = cond && (((piece->getSquare()->getCol()-trackers[EP_COL]==1)) || ((piece->getSquare()->getCol()-trackers[EP_COL]==-1)));
				if (cond) {
					GameMove move;
					move.piece = getBoard()->getSquare(4,piece->getSquare()->getCol())->getPiece();
					move.square = getBoard()->getSquare(5,trackers[EP_COL]);
					move.instr = "wenpassant";
					moves.push_back(move);
					GameMove *parent = &move;
					GameMove *aux0 = new GameMove;
					aux0->piece = NULL;
					aux0->square = getBoard()->getSquare(4,trackers[EP_COL]);
					parent->aux.reset(aux0);
					parent = aux0;
				}
			}
		}
	}
}

void PartialchessGame::promotion() {
	bool cond = true;
	vector <GameMove> temp;
	updateMoves();
	for (vector <GameMove> :: iterator it = moves.begin(); it != moves.end(); it++) {
		GameMove& move = *it;
		if (getCurrentPlayer()->getColour() == WHITE) {
			cond = true;
			cond = cond && ((move.square->getRow()==7));
			cond = cond && ((move.piece->getName() == "pawn"));
			if (cond) {
				GameMove promotion0;
				promotion0.square = move.square;
				promotion0.piece = move.piece;
				promotion0.aux.reset(move.aux.get());
				promotion0.instr = "queen";
				temp.push_back(promotion0);
				GameMove promotion1;
				promotion1.square = move.square;
				promotion1.piece = move.piece;
				promotion1.aux.reset(move.aux.get());
				promotion1.instr = "rook";
				temp.push_back(promotion1);
				GameMove promotion2;
				promotion2.square = move.square;
				promotion2.piece = move.piece;
				promotion2.aux.reset(move.aux.get());
				promotion2.instr = "bishop";
				temp.push_back(promotion2);
				GameMove promotion3;
				promotion3.square = move.square;
				promotion3.piece = move.piece;
				promotion3.aux.reset(move.aux.get());
				promotion3.instr = "knight";
				temp.push_back(promotion3);
				moves.erase(it);
				it--;
			}
		}

	}
	for (vector <GameMove> :: iterator it = temp.begin(); it != temp.end(); it++) {
		moves.push_back(*it);
	}
}

void PartialchessGame::preMove(GameMove& move) {
	bool cond = true;
	cond = true;
	cond = cond && ((move.piece->getSquare()->getRow()==0));
	cond = cond && ((move.piece->getSquare()->getCol()==4));
	if (cond) {
		trackers[WSC]=0;
		trackers[WLC]=0;
	}

	cond = true;
	cond = cond && ((#ROWOF==7));
	cond = cond && ((#COLOF==4));
	if (cond) {
		trackers[BSC]=0;
		trackers[BLC]=0;
	}

	trackersStack.push_back(trackers);
}

void PartialchessGame::postMove(GameMove& move) {
	bool cond = true;
	cond = true;
	cond = cond && ((getRepetition()>trackers[REP]));
	if (cond) {
		trackers[REP]=getRepetition();
	}

	trackersStack.back() = trackers;
}

