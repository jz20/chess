#include "barrunner.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "gamerunner.h"
#include "gameframe.h"
#include "piecebitmap.h"
#include "bargame.h"

using namespace std;

bool BarRunner::OnInit() {
	wxInitAllImageHandlers();
	game = new BarGame();
	unordered_map <string, string> paths;
	paths["white_queen"] = "chess/white_queen.png";
	paths["black_king"] = "chess/black_king.png";
	paths["black_queen"] = "chess/black_queen.png";
	paths["white_king"] = "chess/white_king.png";
	frame = new GameFrame("BarGame", game, this, paths);
	game->setUp();
	frame->updatePieces();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(BarRunner);
