#ifndef PIECE_H
#define PIECE_H

class Piece;

#include <vector>
#include <string>
#include "square.h"
#include "player.h"

class Piece {
    public:
        // Constructor of a piece belonging to a Player at a specific Square
        Piece(Square *square, Player *player);
        // Destructor of a piece
        virtual ~Piece() {}
        // get the square
        Square *getSquare();
        // set the square
        void setSquare(Square *square);
        // update the possible squares for a piece to move to
        virtual void updateTargets() {}
        // get the legal targets
        std::vector <Square *> getTargets();
        // get the player
        Player *getPlayer();
        // return whether the piece functions as a king
        bool isAsKing();
        // get name
        std::string getName();
        // to String
        friend std::ostream& operator<<(std::ostream &strm, const Piece &piece);
    protected:
        // the square that the piece is on
        Square *square;
        // the vector of squares the piece can move to
        std::vector <Square *> targets;
        // the player that the piece belongs to
        Player *player;
        // whether the piece functions as a king
        bool asKing;
        // the name of the piece
        std::string name;
        // the utf-8 representation of the piece
        char symbol;
        /*
        These are auxiliary function that help find the targets
        */
        void upLeftDiag(std::vector <Square *> *targets);
        void downLeftDiag(std::vector <Square *> *targets);
        void upRightDiag(std::vector <Square *> *targets);
        void downRightDiag(std::vector <Square *> *targets);
        void upCol(std::vector <Square *> *targets);
        void downCol(std::vector <Square *> *targets);
        void leftRow(std::vector <Square *> *targets);
        void rightRow(std::vector <Square *> *targets);
        void targetSquare(std::vector <Square *> *targets, int rowOffset, int colOffset);
        // the piece can only move to the target if it causes a capture
        void targetCaptureSquare(std::vector <Square *> *targets, int rowOffset, int colOffset);
        // the piece can only move to the target if it does not cause a capture
        void targetNonCaptureSquare(std::vector <Square *> *targets, int rowOffset, int colOffset);
};

#endif