#include "game.h"

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include "piece.h"
#include "square.h"
#include "player.h"

using namespace std;

// Constructor with the board and the players
Game::Game(Board *board) {
    this->board = board;
    this->white = new Player(WHITE);
    this->black = new Player(BLACK);
    this->moveNo = 0;
    this->finished = false;
    this->inCheck = false;
}

// Destructor of a game
Game::~Game() {
    delete board;
    delete white;
    delete black;
}

// get board
Board *Game::getBoard() {
    return board;
}

// get moves
vector <GameMove> Game::getMoves() {
    return moves;
}

// get turn, the first turn is 1
int Game::getTurn() {
    return moveNo / 2 + 1;
}

// get note
std::string Game::getNote() {
    return note;
}

// get trackers
std::vector <int> Game::getTrackers() {
    return trackers;
}

// set note
void Game::setNote(std::string note) {
    this->note = note;
}

// make the input move, return false if the moveStack is not empty thus the move
// cannot be made
bool Game::makeMove(GameMove& move) {
    if (!moveStack.empty()) {
        return false;
    }
    Piece *piece = move.piece;
    Square *destination = move.square;
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
void Game::tryMove(GameMove& move) {
    tryMove(move, false);
}

// try the input move, store the move on the stack so that it can be reversed
void Game::tryMove(GameMove& move, bool isAux) {
    Piece *piece = move.piece;
    Square *destination = move.square;
    if (piece != NULL) {
        Square *origin = piece->getSquare();
        Piece *captured = destination->getPiece();
        Positioning pOrigin{piece, origin};
        Positioning pDestination{captured, destination};
        move.restoration.push_back(pOrigin);
        move.restoration.push_back(pDestination);
        piece->setSquare(destination);
        if (captured != NULL) {
            captured->setSquare(NULL);
        }
        destination->setPiece(piece);
        origin->setEmpty();
    } else {
        // for aux moves only
        if (destination->getPiece() != NULL) {
            Piece *captured = destination->getPiece();
            Positioning pDestination{captured, destination};
            move.restoration.push_back(pDestination);
            captured->setSquare(NULL);
            destination->setEmpty();
        }
        destination->setEmpty();
    }
    if (!isAux) {
        moveStack.push_back(move);
        moveNo++;
    }
    if (move.aux.get()) {
        tryMove(*(move.aux.get()), true);
    }
}

// reverse last move on the moveStack, returns false if the moveStack is empty
bool Game::reverseLast() {
    if (moveStack.empty()) {
        return false;
    }
    moveNo--;
    GameMove move = moveStack.back();
    reverseMove(move);
    moveStack.pop_back();
    reverseTrackers();
    boardStateStack.pop_back();
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
        return white;
    }
    return black;
}

// get the player whose turn it is not
Player *Game::getOppositePlayer() {
    if (moveNo % 2 == 0) {
        return black;
    }
    return white;
}

// reverse the input move
void Game::reverseMove(GameMove& move) {
    if (move.aux.get()) {
        reverseMove(*(move.aux.get()));
    }
    revertTo(move.restoration);
}

// revert to the input position
void Game::revertTo(vector <Positioning>& revert) {
    Positioning pos;
    for (vector <Positioning> :: iterator it = revert.begin(); 
            it != revert.end(); ++it) {
        pos = *it;
        Square *square = pos.square;
        Piece *piece = pos.piece;
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

// store the board state into the stack
void Game::storeBoardState() {
    string snapshot = board->snapshot();
    boardStateStack.push_back(snapshot);
}

// update the basic moves (the moves that are determined by the usual move 
// rules for each piece)
void Game::basicMoves() {
    vector <Piece *> pieces = getCurrentPlayer()->getPieces();
    Piece *current = NULL;
    for (vector <Piece *> :: iterator it1 = pieces.begin(); it1 != pieces.end(); ++it1) {
        current = *it1;
        if (current->getSquare() != NULL) {
            current->updateTargets();
            vector <Square *> targets = current->getTargets();
            for (vector <Square *> :: iterator it2 = targets.begin(); it2 != targets.end(); ++it2) {
                GameMove move;
                move.piece = current;
                move.square = *it2;
                moves.push_back(move);
            }
        }
    }
}

// get the squares that are controlled by a player
set <Square *> Game::squaresControlled(Player* player) {
    vector <Piece *> pieces = player->getPieces();
    set <Square *> squareSet;
    Piece *current = NULL;
    for (vector <Piece *> :: iterator it = pieces.begin(); it != pieces.end(); ++it) {
        current = *it;
        if (current->getSquare() != NULL) {
            current->updateTargets();
            vector <Square *> currentTargets = current->getTargets();
            copy(currentTargets.begin(), currentTargets.end(),
                    inserter(squareSet, squareSet.end()));
        }
    }
    return squareSet;
}

// test if a player is in check
bool Game::checkTest(Player *player) {
    bool inCheck = false;
    vector <Piece *> kings = player->getColour() == WHITE ? whiteKings : blackKings;
    Player *opposite = player == white ? black : white;
    Piece *king = NULL;
    for (vector <Piece *> :: iterator it = kings.begin(); it != kings.end(); it++) {
        king = *it;
        inCheck = squaresControlled(opposite).count(king->getSquare()) || inCheck;
    }
    return inCheck;
}

// remove the illegal moves from the possible moves
void Game::removeIllegalMoves() {
    GameMove *current = NULL;
    Player *player = getCurrentPlayer();
    for (vector <GameMove> :: iterator it = moves.begin(); it != moves.end(); it++) {
        current = &*it;
        tryMove(*current, false); 
        if (checkTest(player)) {
            moves.erase(it);
            it--;
        }
        reverseLast();
    }
}

// update trackers
void Game::updateTrackers() {
    trackersStack.push_back(trackers);
}

// reverse trackers to the previous state
void Game::reverseTrackers() {
    if (!trackers.empty()) {
        trackersStack.pop_back();
        trackers = trackersStack.back();
    }
}

// promote a piece to a different piece
void Game::promote(Piece *piece, Piece *promotion) {
    Square *square = piece->getSquare();
    piece->setSquare(NULL);
    promotion->setSquare(square);
    square->setPiece(promotion);
    promotion->getPlayer()->addPiece(promotion);
}

// get how many times the last boardstate has been repeated
int Game::getRepetition() {
    string snapshot = board->snapshot();
    int count = 0;
    for (vector <string> :: iterator it = boardStateStack.begin(); 
            it != boardStateStack.end(); it++) {
        if (*it == snapshot) {
            count++;
        }
    }
    return count;
}

// set finished
void Game::setFinished(bool finished) {
    this->finished = finished;
}