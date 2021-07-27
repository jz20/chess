#ifndef PLAYER_H
#define PLAYER_H

class Player;

#define WHITE 0
#define BLACK 1

class Player {
    public:
        // Constructor of a player with the colour of their pieces
        Player(int colour);
        // get colour
        int getColour();
    private:
        int colour;
};

#endif