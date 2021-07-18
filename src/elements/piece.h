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
        // get the square
        Square *getSquare();
        // set the square
        void setSquare(Square *square);
        // update the possible squares for a piece to move to
        virtual void updateMoves();
        // get the legal moves
        std::list <Square *> getMoves();
        // get the player
        Player *getPlayer();
        // return whether the piece functions as a king
        bool isAsKing();
    protected:
        // the square that the piece is on
        Square *square;
        // the list of squares the piece can move to
        std::list <Square *> moves;
        // the player that the piece belongs to
        Player *player;
        // whether the piece functions as a king
        bool asKing;
        /*
        These are auxiliary function that help find the moves
        */
        void upLeftDiag(std::list <Square *> *moves);
        void downLeftDiag(std::list <Square *> *moves);
        void upRightDiag(std::list <Square *> *moves);
        void downRightDiag(std::list <Square *> *moves);
        void upCol(std::list <Square *> *moves);
        void downCol(std::list <Square *> *moves);
        void leftRow(std::list <Square *> *moves);
        void rightRow(std::list <Square *> *moves);
        void targetSquare(std::list <Square *> *moves, int rowOffset, int colOffset);
        // the piece can only move to the target if it causes a capture
        void targetCaptureSquare(std::list <Square *> *moves, int rowOffset, int colOffset);
        // the piece can only move to the target if it does not cause a capture
        void targetNonCaptureSquare(std::list <Square *> *moves, int rowOffset, int colOffset);
};

#endif