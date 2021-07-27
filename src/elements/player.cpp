#include "player.h"

// Constructor of a player with the colour of their pieces
Player::Player(int colour) {
    this->colour = colour;
}
    
// get colour
int Player::getColour() {
    return colour;
}