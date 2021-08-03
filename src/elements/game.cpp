#include "game.h"

#include <vector>
#include <cstddef>
#include "piece.h"
#include "square.h"

using namespace std;

// Constructor with the board and the players
Game::Game(Board *board, Player *player1, Player *player2) {
    this->board = board;
    this->player1 = player1;
    this->player2 = player2;
    this->moveNo = 0;
    this->finished = false;
}

// Destructor of a game
Game::~Game() {
    delete board;
    delete player1;
    delete player2;
}

// get board
Board *Game::getBoard() {
    return board;
}

// get moves
vector <Move *> Game::getMoves() {
    return moves;
}

// get turn, the first turn is 1
int Game::getTurn() {
    return moveNo / 2 + 1;
}

// make the input move, return false if the moveStack is not empty thus the move
// cannot be made
bool Game::makeMove(Move *move) {
    if (!moveStack.empty()) {
        return false;
    }
    Piece *piece = move->piece;
    Square *destination = move->square;
    Square *origin = piece->getSquare();
    if (destination->getPiece() != NULL) {
        getOppositePlayer()->removePiece(destination->getPiece());
    }
    piece->setSquare(destination);
    destination->setPiece(piece);
    origin->setEmpty();
    return true;
}

// try the input move, store the move on the stack so that it can be reversed
void Game::tryMove(Move *move) {
    tryMove(move, false);
}

// try the input move, store the move on the stack so that it can be reversed
void Game::tryMove(Move *move, bool isAux) {
    Piece *piece = move->piece;
    Square *destination = move->square;
    Square *origin = piece->getSquare();
    Piece *captured = destination->getPiece();
    Positioning *pOrigin = new Positioning;
    *pOrigin = {piece, origin};
    Positioning *pDestination = new Positioning;
    *pDestination = {captured, destination};
    move->restoration.push_back(pOrigin);
    move->restoration.push_back(pDestination);
    piece->setSquare(destination);
    if (captured != NULL) {
        captured->setSquare(NULL);
    }
    destination->setPiece(piece);
    origin->setEmpty();
    if (!isAux) {
        moveStack.push_back(move);
        moveNo++;
    }
    if (move->aux) {
        tryMove(move->aux, true);
    }
}

// reverse last move on the moveStack, returns false if the moveStack is empty
bool Game::reverseLast() {
    if (moveStack.empty()) {
        return false;
    }
    Move *move = moveStack.back();
    reverseMove(move);
    moveStack.pop_back();
    return true;
}

// get the size of the moveStack
int Game::getMoveStackSize() {
    return moveStack.size();
}

// is finished
bool Game::isFinished() {
    return finished;
}

// get the player whose turn it is
Player *Game::getCurrentPlayer() {
    if (moveNo % 2 == 0) {
        return player1;
    }
    return player2;
}

// get the player whose turn it is not
Player *Game::getOppositePlayer() {
    if (moveNo % 2 == 0) {
        return player2;
    }
    return player1;
}

// reverse the input move
void Game::reverseMove(Move *move) {
    if (move->aux) {
        reverseMove(move->aux);
    }
    revertTo(&(move->restoration));
}

// revert to the input position
void Game::revertTo(vector <Positioning *> *revert) {
    Positioning *pos;
    for (vector <Positioning *> :: iterator it = revert->begin(); 
            it != revert->end(); ++it) {
        pos = *it;
        Square *square = pos->square;
        Piece *piece = pos->piece;
        if (piece != NULL) {
            if (piece->getSquare() && piece->getSquare()->getPiece() == piece) {
                piece->getSquare()->setEmpty();
            }
            piece->setSquare(square);
        }
        if (!square->isEmpty() && square->getPiece()->getSquare() == square) {
            square->getPiece()->setSquare(NULL);
        }
        square->setPiece(piece);
    }
}