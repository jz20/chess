#ifndef GAME_FRAME_H
#define GAME_FRAME_H

class GameFrame;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "piecebitmap.h"
#include "gamerunner.h"

class GameFrame: public wxFrame {
    public: 
        GameFrame(const wxString title, Game *game, GameRunner *runner,
                std::unordered_map <std::string, std::string> paths);
        // update the pieces in the board
        void updatePieces();
        // take the mouse input
        void input(Square *square);
    private:
        // the game app that is using this frame
        GameRunner *runner;
        // the size of a square
        int squareSize;
        // the number of rows
        int rows;
        // the number of columns
        int cols;
        // the square panels
        std::vector <wxPanel *> pSquares;
        // the map from the square to the pieces
        std::unordered_map <wxPanel *, wxStaticBitmap *> pieceMap;
        // the map from the piece types to the paths of their files
        std::unordered_map <std::string, std::string> paths;
        // the board panel
        wxPanel *pBoard;
        // the game
        Game *game;
        // called when the window closes
        void onClose(wxCommandEvent& event);
};

#endif