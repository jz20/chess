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
    unordered_map <string, string> paths;
    paths["white_king"] = "chess/white_king.png";
    paths["white_queen"] = "chess/white_queen.png";
    paths["white_knight"] = "chess/white_knight.png";
    paths["white_rook"] = "chess/white_rook.png";
    paths["white_bishop"] = "chess/white_bishop.png";
    paths["white_pawn"] = "chess/white_pawn.png";
    paths["black_king"] = "chess/black_king.png";
    paths["black_queen"] = "chess/black_queen.png";
    paths["black_knight"] = "chess/black_knight.png";
    paths["black_rook"] = "chess/black_rook.png";
    paths["black_bishop"] = "chess/black_bishop.png";
    paths["black_pawn"] = "chess/black_pawn.png";
    frame = new GameFrame("Chess Game", game, this, paths, "../../img/");
    game->setUp();
    frame->updatePieces();
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(ChessGameRunner);