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