#ifndef CHESS_PIECE_BITMAP
#define CHESS_PIECE_BITMAP

class ChessPieceBitmap;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "chessgamerunner.h"
#include "piece.h"

class ChessPieceBitmap: public wxStaticBitmap {
    public:
        ChessPieceBitmap(wxWindow *parent, wxWindowID id, const wxBitmap &label,
                const wxPoint &pos, const wxSize &size, long style);
        ~ChessPieceBitmap();
    private:
        ChessGameRunner *runner;
        Piece *piece;
        void onClick(wxMouseEvent& event);
};




#endif