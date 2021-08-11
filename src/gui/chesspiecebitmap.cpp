#include "chesspiecebitmap.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "chessgamerunner.h"
#include <iostream>

ChessPieceBitmap::ChessPieceBitmap(wxWindow *parent, wxWindowID id, const wxBitmap &label,
        const wxPoint &pos, const wxSize &size, long style, Square *square, ChessGameRunner *runner):
        wxStaticBitmap(parent, id, label, pos, size, style) {
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler (ChessPieceBitmap::onClick), NULL, this);
    this->runner = runner;
    this->square = square;
}

ChessPieceBitmap::~ChessPieceBitmap() {
}

void ChessPieceBitmap::onClick(wxMouseEvent& event) {
    runner->input(square);
}