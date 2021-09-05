#ifndef PIECE_BITMAP_H
#define PIECE_BITMAP_H

class PieceBitMap;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "piece.h"
#include "gameframe.h"
#include "gamerunner.h"

class PieceBitmap: public wxStaticBitmap {
    public:
        PieceBitmap(wxWindow *parent, wxWindowID id, const wxBitmap &label,
                const wxPoint &pos, const wxSize &size, long style, Square *square, GameRunner *runner);
    private:
        GameRunner *runner;
        Square *square;
        void onClick(wxMouseEvent& event);
};

#endif