#ifndef CHESS_GAME_RUNNER_H
#define CHESS_GAME_RUNNER_H

class ChessGameRunner;
class ChessGameFrame;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "chessgame.h"
#include "chesspiecebitmap.h"


class ChessGameRunner: public wxApp {
    public:
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
        // show frame
        void showFrame();
    private:
        Game *game;
        // the move propose by the user
        GameMove proposal;
        // virtual int OnExit();
        // the main frame of the application
        ChessGameFrame *frame;
};

class ChessGameFrame: public wxFrame {
    public: 
        ChessGameFrame(const wxString title, Game *game, ChessGameRunner *runner);
        // update the pieces in the board
        void updatePieces();
    private:
        // the game app that is using this frame
        ChessGameRunner *runner;
        // the size of a square
        int squareSize;
        // the square panels
        std::vector <wxPanel *> pSquares;
        // the map from the square to the pieces
        std::unordered_map <wxPanel *, wxStaticBitmap *> pieceMap;
        // the board panel
        wxPanel *pBoard;
        // the game
        Game *game;
};



/*
wxBEGIN_EVENT_TABLE(ChessGame, wxFrame)

wxEND_EVENT_TABLE()
*/

/*
int main();
*/

#endif