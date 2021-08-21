#ifndef CHESS_GAME_H
#define CHESS_GAME_H

class ChessGame;

#include "game.h"
#include <vector>
#include <set>

typedef struct Flags {
    // white short castle right
    bool WSC;
    // white long castle right
    bool WLC;
    // black short castle right
    bool BSC;
    // black long castle right
    bool BLC;
    // the col with the possibility of en passant capture, -1 signifies none
    int EP_COL;
    // 50 move rule, implemented as such that single player move increments it
    // by one, thus needed to be divided by 2 when checked
    int FIFTY;
    // 3-fold repetition
    int REP;
} Flags;

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
        // the indicator flags belonging to a chess game;
        Flags flags;
        // white king
        Piece *whiteKing;
        // black king
        Piece *blackKing;
        // the stack of flags
        std::vector <Flags> flagsStack;
        // update pawns' two-square moves
        void pawnTwoSquare();
        // update the castling moves
        void castling();
        // update the en passant captures
        void enPassant();
        // update the promotion moves
        void promotion();
        // update the flags;
        void updateFlags(GameMove& move);
        // reverse flags to the previous state
        void reverseFlags();
        // check if there is insufficient material on the board such that
        // there would be a draw, if so return true
        bool insufficientMaterial();
        // get the pieces that have not been captured, excluding the kings
        std::vector <Piece *> getActivePieces();
        // store the board state into the stack, check for 3-fold repetition
        virtual void storeBoardState();
        // reverse trackers to the previous state
        virtual void updateTrackers(GameMove& move);
};

#endif
