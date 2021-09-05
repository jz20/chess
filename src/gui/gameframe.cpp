#include "gameframe.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "piecebitmap.h"
#include "gamerunner.h"

using namespace std;

#define SQUARE_SIZE 64

//wxFrame(NULL, wxID_ANY, title, pos, size)
GameFrame::GameFrame(const wxString title, Game* game, GameRunner *runner, 
        unordered_map <string, string> paths) {
    Connect(wxEVT_CLOSE_WINDOW, wxCommandEventHandler(GameFrame::onClose), NULL, this);
    this->runner = runner;
    this->paths = paths;
    this->game = game;
    squareSize = SQUARE_SIZE;
    Board *board = game->getBoard();
    rows = board->getRows();
    cols = board->getCols();
    int xPos = 0;
    int yPos = (rows - 1) * squareSize;
    int extra = 50;
    wxColour light = wxColour(240,176,87);
    wxColour dark = wxColour(137,82,23);
    Create(0, wxID_ANY, title, wxPoint(0, 0), wxSize(rows * squareSize, cols * squareSize + extra), wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    pBoard = new wxPanel(this, wxNewId(), wxPoint(0, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            wxWindowID id = wxNewId();
            wxPanel* pSquare = new wxPanel(pBoard, id, wxPoint(xPos, yPos),
                    wxSize(squareSize, squareSize));
            if ((i + j) % 2 == 0) {
                pSquare->SetBackgroundColour(light);
            } else {
                pSquare->SetBackgroundColour(dark);
            }
            pSquares.push_back(pSquare);
            PieceBitmap *img;
            wxString path = "../../img/chess/empty.png";
            img = new PieceBitmap(pSquare, wxNewId(), 
            wxBitmap(wxImage(path).Rescale(squareSize, squareSize)),
                    wxPoint(0, 0), wxSize(squareSize, squareSize), 0, board->getSquare(i, j), runner);
            pieceMap[pSquare] = img;
            xPos += squareSize;
        }
        xPos = 0;
        yPos -= squareSize;
    }
    FitInside();
    updatePieces();
}

void GameFrame::updatePieces() {
    int count = 0;
    int row = 0;
    int col = 0;
    Board *board = game->getBoard();
    count = 0;
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
        row = count / rows;
        col = count % rows;
        Piece *piece = board->getSquare(row, col)->getPiece();
        wxString path = "../../img/";
        string name = "";
        if (piece != NULL) {
            if (piece->getPlayer()->getColour() == WHITE) {
                name += "white_";
            } else {
                name += "black_";
            }
            name += piece->getName();
            if (paths.find(name) != paths.end()) {
                path += paths[name];
            }
        } else {
            path += "empty.png";
        }
        pieceMap[*it]->SetBitmap(wxBitmap(wxImage(path).Rescale(squareSize, squareSize)));
        count++;
    }
}

// called when the window closes
void GameFrame::onClose(wxCommandEvent& event) {
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
        if (pieceMap.count(*it) > 0 && pieceMap[*it]) {
            delete pieceMap[*it];
        }
        delete *it;
    }
    pSquares.clear();
    // runner->finishGame();
    Destroy();
}