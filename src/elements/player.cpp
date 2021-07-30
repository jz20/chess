#include "player.h"

#include <vector>
#include "piece.h"

using namespace std;

// Constructor of a player with the colour of their pieces
Player::Player(Colour colour) {
    this->colour = colour;
}

// Destructor of a player
Player::~Player() {
    for (vector <Piece *> :: iterator it = pieces.begin(); it != pieces.end(); ++it) {
        delete *it;
    }
}
    
// get colour
Colour Player::getColour() {
    return colour;
}

// add a piece to the vector of the player's pieces, requiring that the piece
// belongs to the player
bool Player::addPiece(Piece *piece) {
    if (piece->getPlayer() == this) {
        pieces.push_back(piece);
    }
    return false;
}

// remove a piece from the player's possession as well as destroying it,
// returning true if successful and false otherwise (requiring that the 
// piece is found)
bool Player::removePiece(Piece *piece) {
    for (vector <Piece *> :: iterator it = pieces.begin(); it != pieces.end(); ++it) {
        if (*it = piece) {
            pieces.erase(it);
            return true;
        }
    }
    return false;
}