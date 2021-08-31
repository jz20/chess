#ifndef GAME_H
#define GAME_H

struct Positioning;
typedef struct Positioning Positioning;
struct GameMove;
typedef struct GameMove GameMove;
struct Flags;
typedef struct Flags Flags;

class Game;

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <set>
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
} GameMove;

class Game {
    public:
        // Constructor with the board and the players 
        Game(Board *board);
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
        Player *white;
        // the player who moves second
        Player *black;
        // record the board state in the game
        std::vector <std::string> boardStateStack;
        // the dynamic move storage, storing the legal moves for the player to 
        // move
        std::vector <GameMove> moves;
        // the stack of moves for trial and reverse
        std::vector <GameMove> moveStack;
        // the vector containing the white king(s)
        std::vector <Piece *> whiteKings;
        // the vector containing the black king(s)
        std::vector <Piece *> blackKings;
        // the trackers that a game uses
        std::vector <int> trackers;
        // the trackers that a game uses
        std::vector <std::vector <int>> trackersStack;
        // reverse the input move
        void reverseMove(GameMove& move);
        // revert to the input position
        void revertTo(std::vector <Positioning>& pos);
        // store the board state into the stack, check for 3-fold repetition
        virtual void storeBoardState();
        // update the basic moves (the moves that are determined by the usual move 
        // rules for each piece)
        void basicMoves();
        // get the squares that are controlled by a player
        std::set <Square *> squaresControlled(Player* player);
        // test if a player is in check
        bool checkTest(Player *player);
        // remove the illegal moves from the possible moves
        void removeIllegalMoves();
        // get the size of the moveStack
        int getMoveStackSize();
        // reverse last move on the moveStack, returns false if the moveStack is 
        // empty
        virtual bool reverseLast();
        // update trackers
        virtual void updateTrackers();
        // reverse trackers to the previous state
        virtual void reverseTrackers();
        // promote a piece to a different piece
        void promote(Piece *piece, Piece *promotion);
        // get how many times the last boardstate has been repeated
        int getRepetition();
};

#endif
