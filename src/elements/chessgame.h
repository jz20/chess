#ifndef CHESS_GAME_H
#define CHESS_GAME_H

class ChessGame;

#include "game.h"
#include <vector>
#include <set>

// WSC: white short castle right
// WLC: white long castle right
// BSC: black short castle right
// BLC: black long castle right
// EP_COL: the col with the possibility of en passant capture, -1 signifies none
// FIFTY: 50 move rule, implemented as such that single player move increments it
// by one, thus needed to be divided by 2 when checked
// REP: 3-fold repetition
typedef enum {WSC, WLC, BSC, BLC, EP_COL, FIFTY, REP, num_TRACKERS} TrackerId;


class ChessGame: public Game {
    public:
        // Constructor with the board and the players
        ChessGame();
        // Destructor of ChessGame
        ~ChessGame();
        // update the moves that a player can make
        void updateMoves();
        // set up the pieces for the board and the players
        void setUp();
        // check if the game is over, set finished to be true if so, return
        // true if a player wins and false if there is a draw, the result is 
        // meaningless unless finished is true
        virtual bool checkResult();
        // try the input move, store the move on the stack so that it can be 
        // reversed
        virtual void tryMove(GameMove& move, bool isAux);
        // try the input move, store the move on the stack so that it can be 
        // reversed, default non-aux move
        virtual void tryMove(GameMove& move);
        // reverse last move on the moveStack, returns false if the moveStack is 
        // empty
        bool reverseLast();
    private:
        // white king
        Piece *whiteKing;
        // black king
        Piece *blackKing;
        // update pawns' two-square moves
        void pawnTwoSquare();
        // update the castling moves
        void castling();
        // update the en passant captures
        void enPassant();
        // update the promotion moves
        void promotion();
        // check the threefold repetition rule
        void checkRepetition();
        // check if there is insufficient material on the board such that
        // there would be a draw, if so return true
        bool insufficientMaterial();
        // get the pieces that have not been captured, excluding the kings
        std::vector <Piece *> getActivePieces();
        // reverse trackers to the previous state
        virtual void updateTrackers(GameMove& move);
};

#endif
