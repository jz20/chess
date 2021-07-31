#ifndef CHESS_GAME_H
#define CHESS_GAME_H

class ChessGame;

#include "game.h"
#include <vector>
#include <set>

class ChessGame: public Game {
    public:
        // Constructor with the board and the players
        ChessGame();
        // Destructor of ChessGame
        ~ChessGame();
        // update the moves that a player can make
        void updateMoves();
        // make the input move, return false if the moveStack is empty thus the move
        // cannot be made
        bool makeMove(Move *move);
        // try the input move, store the move on the stack so that it can be 
        // reversed
        void tryMove(Move *move, bool isAux);
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
        // update the basic moves (the moves that are determined by the usual move 
        // rules for each piece)
        void basicMoves();
        // update pawns' two-square moves
        void pawnTwoSquare();
        // update the castling moves
        void castling(std::set <Square *> opponentControlled);
        // update the en passant captures
        void enPassant();
        // update the promotion moves
        void promotion();
        // get the squares that are controlled by a player
        std::set <Square *> squaresControlled(Player* player);
        // test if a player is in check
        bool checkTest();
};

#endif
