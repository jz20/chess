#include "chesssquarepanel.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "chessgamerunner.h"


ChessSquarePanel::ChessSquarePanel(wxWindow *parent, wxWindowID id, const wxPoint point,
        const wxSize size, Square *square, ChessGameRunner *runner):
        wxPanel(parent, id, point, size) {
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler (ChessSquarePanel::onClick), NULL, this);
    this->square = square;
    this->runner = runner;
}

ChessSquarePanel::~ChessSquarePanel() {
}

void ChessSquarePanel::onClick(wxMouseEvent& event) {
    runner->inputSquare(square);
}