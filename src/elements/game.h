#ifndef GAME_H
#define GAME_H

class Game;

#include <cstddef>
#include <vector>
#include <string>
#include "piece.h"
#include "square.h"

typedef struct Positioning {
    Piece *piece;
    Square *square;
} Positioning;

typedef struct Move {
    Move() : piece(NULL), square(NULL), aux(NULL), instr("") {}
    Piece *piece;
    Square *square;
    Move *aux;
    std::string instr;
    std::vector <Positioning *> restoration; // used for trial and reverse
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
        // make the input move, return false if the moveStack is empty thus the
        // move cannot be made
        bool makeMove(Move *move);
        // is finished
        bool isFinished();
        // get the player whose turn it is
        Player *getCurrentPlayer();
        // get the player whose turn it is not
        Player *getOppositePlayer();
        // try the input move, store the move on the stack so that it can be 
        // reversed
        void tryMove(Move *move, bool aux);
        // reverse last move on the moveStack, returns false if the moveStack is 
        // empty
        bool reverseLast();
        // get the size of the moveStack
        int getMoveStackSize();
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
        // the stack of moves for trial and reverse
        std::vector <Move *> moveStack;
        // reverse the input move
        void reverseMove(Move *move);
        // revert to the input position
        void revertTo(std::vector <Positioning *> *pos);
};

#endif