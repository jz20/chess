#ifndef GAME_H
#define GAME_H

class Game;

#include <cstddef>
#include <vector>
#include <string>
#include "piece.h"
#include "square.h"

typedef struct Move {
    Move() : piece(NULL), square(NULL), aux(NULL), instr("") {}
    Piece *piece;
    Square *square;
    Move *aux;
    std::string instr;
} Move;

class Game {
    public:
        // Constructor with the board and the players 
        Game(Board *board, Player *player1, Player *player2);
        // Destructor of a game
        ~Game();
        // update the moves that a player can make
        virtual void updateMoves() {}
        // get moves
        std::vector <Move *> getMoves();
        // get turn, the first turn is 1
        int getTurn();
        // make the input move
        void makeMove(Move *move);
        // is finished
        bool isFinished();
        // get the player whose turn it is
        Player *getCurrentPlayer();
        // get the player whose turn it is not
        Player *getOppositePlayer();
    protected:
        // whether the game is finished;
        bool finished;
        // whether the player is in check
        bool inCheck;
        // the current move number, the first move is 0
        int moveNo;
        // the board to play with
        Board *board;
        // the player who moves first
        Player *player1;
        // the player who moves second
        Player *player2;
        // the dynamic move storage, storing the legal moves for the player to 
        // move
        std::vector <Move *> moves;
};

#endif