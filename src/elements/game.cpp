#include "game.h"

#include <vector>
#include <cstddef>
#include "piece.h"
#include "square.h"

// Constructor with the board and the players
Game::Game(Board *board, Player *player1, Player *player2) {
    this->board = board;
    this->player1 = player1;
    this->player2 = player2;
}

// Destructor of a game
Game::~Game() {
    delete board;
    delete player1;
    delete player2;
}

// get moves
std::vector <Move *> Game::getMoves() {
    return moves;
}

// get turn, the first turn is 1
int Game::getTurn() {
    return moveNo / 2 + 1;
}

// make the input move
void Game::makeMove(Move *move) {
    Piece *piece = move->piece;
    Square *destination = move->square;
    Square *origin = piece->getSquare();
    if (destination->getPiece() != NULL) {
        getOppositePlayer()->removePiece(destination->getPiece());
    }
    piece->setSquare(destination);
    destination->setPiece(piece);
    origin->setEmpty();
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