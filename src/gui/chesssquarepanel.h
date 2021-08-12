#ifndef SQUARE_PANEL_H
#define SQUARE_PANEL_H

class ChessSquarePanel;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "chessgamerunner.h"
#include "square.h"

class ChessSquarePanel: public wxPanel {

    public:
        ChessSquarePanel(wxWindow *parent, wxWindowID id, const wxPoint point,
            const wxSize size, Square *square, ChessGameRunner *runner);
        ~ChessSquarePanel();
        void onClick(wxMouseEvent& event);
    private:
        Square *square;
        ChessGameRunner *runner;
};




#endif