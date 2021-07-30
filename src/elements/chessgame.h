#ifndef CHESS_GAME_H
#define CHESS_GAME_H

class ChessGame;

#include "game.h"

typedef enum {NA = 0, QUEEN = 1, ROOK = 2, BISHOP = 3, KNIGHT = 4} Promotion;
typedef struct Castle {
    bool happens;
    Move *rookMove;
} Castle;

class ChessGame: public Game {
    public:
        // Constructor with the board and the players
        ChessGame();
        // Destructor of ChessGame
        ~ChessGame();
        // update the moves that a player can make
        void updateMoves();
        // make the input move
        void makeMove(Move *move, Castle castle, Promotion promotion, bool enPassant);
    private:
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
        // returns a Castle object that does not happen
        Castle noCastle();
        // update the basic moves (the moves that are determined by the usual move 
        // rules for each piece)
        void basicMoves();
        // update pawns' two-square moves
        void pawnTwoSquare();

};

#endif
