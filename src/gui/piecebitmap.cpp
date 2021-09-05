#include "piecebitmap.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "piece.h"

PieceBitmap::PieceBitmap(wxWindow *parent, wxWindowID id, const wxBitmap &label,
        const wxPoint &pos, const wxSize &size, long style, Square *square, GameRunner *runner):
        wxStaticBitmap(parent, id, label, pos, size, style) {
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(PieceBitmap::onClick), NULL, this);
    this->runner = runner;
    this->square = square;
}

void PieceBitmap::onClick(wxMouseEvent& event) {
    runner->input(square);
}