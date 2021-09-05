#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

class GameRunner;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "piecebitmap.h"

// sub classes need to provide implementation of OnInit
class GameRunner: public wxApp {
    public:
        // initialisation, to be implemented by subclasses
        virtual bool OnInit();
        // input a raw value, call inputPiece or inputRow accordingly
        bool input(Square *square);
        // clear the information in the proposal move
        bool inputPiece(Piece *piece);
        // input the move square in the proposal move
        bool inputSquare(Square *square);
        // clear the information in the proposal move
        void clearProposal();
        // run the game cycle
        void gameCycle();
        // get the actual move
        GameMove actualMove();
        // finish game: call destructor of game
        void finishGame();
    protected:
        Game *game;
        // the move propose by the user
        GameMove proposal;
        // the main frame of the application
        GameFrame *frame;
};

#endif