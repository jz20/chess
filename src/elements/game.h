#ifndef GAME_H
#define GAME_H

struct Positioning;
typedef struct Positioning Positioning;
struct GameMove;
typedef struct GameMove GameMove;
class Game;

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "square.h"

typedef struct Positioning {
    Piece *piece;
    Square *square;
} Positioning;

typedef struct GameMove {
    GameMove() : piece(NULL), square(NULL), aux(NULL), instr("") {}
    Piece *piece;
    Square *square;
    std::shared_ptr <GameMove> aux;
    std::string instr;
    std::vector <Positioning> restoration; // used for trial and reverse
    ~GameMove() {
        restoration.clear();
    }
} GameMove;

class Game {
    public:
        // Constructor with the board and the players 
        Game(Board *board, Player *player1, Player *player2);
        // Destructor of a game
        virtual ~Game();
        // update the moves that a player can make
        virtual void updateMoves() {}
        // set up the board and the players
        virtual void setUp() {}
        // check if the game is over, set finished to be true if so, return
        // true if a player wins and false if there is a draw, the result is 
        // meaningless unless finished is true
        virtual bool checkResult() { return false; }
        // get board
        Board *getBoard();
        // get moves
        std::vector <GameMove> getMoves();
        // get turn, the first turn is 1
        int getTurn();
        // get note
        std::string getNote();
        // set note
        void setNote(std::string note);
        // make the input move, return false if the moveStack is not empty thus the
        // move cannot be made
        bool makeMove(GameMove& move);
        // is finished
        bool isFinished();
        // get the player whose turn it is
        Player *getCurrentPlayer();
        // get the player whose turn it is not
        Player *getOppositePlayer();
        // try the input move, store the move on the stack so that it can be 
        // reversed
        virtual void tryMove(GameMove& move, bool aux);
        // try the input move, store the move on the stack so that it can be 
        // reversed, default non-aux move
        virtual void tryMove(GameMove& move);
        // reverse last move on the moveStack, returns false if the moveStack is 
        // empty
        virtual bool reverseLast();
        // get the size of the moveStack
        int getMoveStackSize();
    protected:
        // whether the game is finished;
        bool finished;
        // whether the player is in check
        bool inCheck;
        // the current move number, the first move is 0
        int moveNo;
        // the note of the game state for storing information that the game 
        // runner might use
        std::string note;
        // the board to play with
        Board *board;
        // the player who moves first
        Player *player1;
        // the player who moves second
        Player *player2;
        // the dynamic move storage, storing the legal moves for the player to 
        // move
        std::vector <GameMove> moves;
        // the stack of moves for trial and reverse
        std::vector <GameMove> moveStack;
        // reverse the input move
        void reverseMove(GameMove& move);
        // revert to the input position
        void revertTo(std::vector <Positioning>& pos);
};

#endif