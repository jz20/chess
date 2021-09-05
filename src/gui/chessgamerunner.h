#ifndef CHESS_GAME_RUNNER_H
#define CHESS_GAME_RUNNER_H

class ChessGameRunner;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "chessgame.h"
#include "gamerunner.h"
#include "gameframe.h"
#include "chesspiecebitmap.h"


class ChessGameRunner: public GameRunner {
    public:
        // initialise the game
        virtual bool OnInit();
    private:
};

#endif