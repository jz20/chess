#ifndef PIECE_H
#define PIECE_H

class Piece;

#include <list>
#include "square.h"
#include "player.h"

class Piece {
    public:
        // Constructor of a piece belonging to a Player at a specific Square
        Piece(Square *square, Player *player);
        // Constructor of a piece belonging to a Player
        Piece(Player *player);
        // get the square
        Square *getSquare();
        // set the square
        void setSquare(Square *square);
        // update the legal moves of a piece
        virtual void updateMoves();
        // get the legal moves
        std::list <Square *> getMoves();
        // get the player
        Player *getPlayer();
    protected:
        // the square that the piece is on
        Square *square;
        // the list of squares the piece can move to
        std::list <Square *> moves;
        // the player that the piece belongs to
        Player *player;
        /*
        These are auxiliary function that help find the moves
        */
        void upLeftDiag(std::list <Square *> *moves);
        void downLeftDiag(std::list <Square *> *moves);
        void upRightDiag(std::list <Square *> *moves);
        void downRightDiag(std::list <Square *> *moves);
};

#endif