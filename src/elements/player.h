#ifndef PLAYER_H
#define PLAYER_H

class Player;

#include <vector>
#include "piece.h"

typedef enum {WHITE, BLACK} Colour;

class Player {
    public:
        // Constructor of a player with the colour of their pieces
        Player(Colour colour);
        // Destructor of a player
        ~Player();
        // get colour
        Colour getColour();
        // add a piece to the vector of the player's pieces, returning true if
        // successful and false otherwise (requiring that the piece belongs to 
        // the player)
        bool addPiece(Piece *piece);
        // remove a piece from the player's possession as well as destroying it,
        // returning true if successful and false otherwise (requiring that the 
        // piece is found)
        bool removePiece(Piece *piece);
    private:
        // the color of the player's pieces
        Colour colour;
        // the vector of the player's pieces
        std::vector <Piece *> pieces;
};

#endif