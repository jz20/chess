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

class ChessGame: public Game {
    public:
        // Constructor with the board and the players
        ChessGame();
        // Destructor of ChessGame
        ~ChessGame();
        // update the moves that a player can make
        void updateMoves();
        // make the input move, return false if the moveStack is not empty thus the move
        // cannot be made
        bool makeMove(Move *move);
        // set up the pieces for the board and the players
        void setUp();
        // check if the game is over, set finished to be true if so, return
        // true if a player wins and false if there is a draw, the result is 
        // meaningless unless finished is true
        bool checkResult();
        // try the input move, store the move on the stack so that it can be 
        // reversed
        void tryMove(Move *move, bool isAux);
        // reverse last move on the moveStack, returns false if the moveStack is 
        // empty
        bool reverseLast();
    private:
        // the indicator flags belonging to a chess game;
        Flags *flags;
        // white king
        Piece *whiteKing;
        // black king
        Piece *blackKing;
        // the stack of flags
        std::vector <Flags *> flagsStack;
        // update the basic moves (the moves that are determined by the usual move 
        // rules for each piece)
        void basicMoves();
        // update pawns' two-square moves
        void pawnTwoSquare();
        // update the castling moves
        void castling();
        // update the en passant captures
        void enPassant();
        // update the promotion moves
        void promotion();
        // remove the illegal moves from the possible moves
        void removeIllegalMoves();
        // get the squares that are controlled by a player
        std::set <Square *> squaresControlled(Player* player);
        // test if a player is in check
        bool checkTest(Player *player);
        // update the flags;
        void updateFlags(Move *move);
        // reverse flags to the previous state
        void reverseFlags();
        // check if there is insufficient material on the board such that
        // there would be a draw, if so return true
        bool insufficientMaterial();
        // get the pieces that have not been captured, excluding the kings
        std::vector <Piece *> getActivePieces();
};

#endif
