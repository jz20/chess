#ifndef BAR_RUNNER_H
#define BAR_RUNNER_H

class BarRunner;

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

class BarRunner: public GameRunner {
	public:
		virtual bool OnInit();
};

#endif
