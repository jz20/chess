#include "chessgamerunner.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/wfstream.h>
#include <wx/bitmap.h>
#include <vector>
#include <string>
#include "game.h"
#include "chessgame.h"

using namespace std;


bool ChessGameRunner::OnInit() {
    wxInitAllImageHandlers();
    game = new ChessGame();
    unordered_map <string, string> a;
    a["white_king"] = "chess/white_king.png";
    a["white_queen"] = "chess/white_queen.png";
    a["white_knight"] = "chess/white_knight.png";
    a["white_rook"] = "chess/white_rook.png";
    a["white_bishop"] = "chess/white_bishop.png";
    a["white_pawn"] = "chess/white_pawn.png";
    a["black_king"] = "chess/black_king.png";
    a["black_queen"] = "chess/black_queen.png";
    a["black_knight"] = "chess/black_knight.png";
    a["black_rook"] = "chess/black_rook.png";
    a["black_bishop"] = "chess/black_bishop.png";
    a["black_pawn"] = "chess/black_pawn.png";
    frame = new GameFrame("Chess Game", game, this, a);
    game->setUp();
    frame->updatePieces();
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(ChessGameRunner);