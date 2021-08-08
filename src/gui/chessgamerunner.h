#ifndef CHESS_GAME_RUNNER_H
#define CHESS_GAME_RUNNER_H

class ChessGameRunner;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include <game.h>
#include <chessgame.h>


class ChessGameRunner: public wxApp {
    public:
        virtual bool OnInit();

        // input the move piece
        bool inputPiece(int row, int col);
        // input the move square in the proposal move
        void inputSquare(int row, int col);
        // clear the information in the proposal move
        void clearMove();
        // get pointer to proposal move
        GameMove *ptrProposal();
        // get the actual move
        GameMove *actualMove(GameMove *prop);
    private:
        Game *game;
        // the move propose by the user
        GameMove proposal;
        // virtual int OnExit();
};

class ChessGameFrame: public wxFrame {
    public: 
        ChessGameFrame(const wxString title, Game *game);
        // update the pieces in the board
        void updatePieces();
    private:
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