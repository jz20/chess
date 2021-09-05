#include "gamerunner.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <vector>
#include <unordered_map>
#include "game.h"
#include "chessgame.h"
#include "piecebitmap.h"
#include "gameframe.h"

using namespace std;

// to be implemented by subclasses
bool GameRunner::OnInit() {
    return false;
}

// wxIMPLEMENT_APP(GameRunner);

// get the actual move
GameMove GameRunner::actualMove() {
    GameMove move;
    vector <GameMove> moves = game->getMoves();
    vector <GameMove> candidates;
    for (vector <GameMove> :: iterator it = moves.begin(); it != moves.end(); it++) {
        move = *it;
        if (move.piece == (proposal.piece)
                && move.square == (proposal.square)) {
            candidates.push_back(move);
        }
    }
    if (candidates.size() == 0) {
        move.instr = "unavailable";
        return move;
    } else if (candidates.size() == 1) {
        return candidates.front();
    } else {
        wxArrayString choices;
        for (vector <GameMove> :: iterator it = candidates.begin(); it != candidates.end(); it++) {
            choices.Add(it->instr);
        }
        wxSingleChoiceDialog *dial = new wxSingleChoiceDialog(NULL, 
                    wxT("Choose an action:"), wxT("Promotion"), choices);
            dial->ShowModal();
        return candidates[dial->GetSelection()];
    }
}

void GameRunner::gameCycle() {
    game->updateMoves();
    GameMove move = actualMove();
    if (move.instr != "unavailable") {
        // cout << move.instr << "\n";
        game->tryMove(move);
        frame->updatePieces();
        bool result = game->checkResult();
        if (game->isFinished()) {
            wxString msg = "";
            if (result) {
                if (game->getCurrentPlayer()->getColour() == WHITE) {
                    msg = "Black wins.";
                } else {
                    msg = "White wins.";
                }
            } else {
                msg = "Draw.";
            }
            wxMessageDialog *dial = new wxMessageDialog(NULL, 
                            msg, wxT("Good Game"), 
                            wxOK | wxICON_INFORMATION);
                    dial->ShowModal();
        }
    }
    clearProposal();
}

// input raw row and col values, call inputPiece or inputRow accordingly
bool GameRunner::input(Square *square) {
    if (proposal.piece == NULL) {
        if (square->getPiece() != NULL) {
            return inputPiece(square->getPiece());
        } else {
            return false;
        }
    } else {
        if (square->getPiece() != NULL && proposal.piece->getPlayer() == square->getPiece()->getPlayer()) {
            return inputPiece(square->getPiece());
        }
        return inputSquare(square);
    }
}

// input the move piece in the proposal move
bool GameRunner::inputPiece(Piece *piece) {
    proposal.piece = piece;
    return true;
}

// input the move square in the proposal move
bool GameRunner::inputSquare(Square *square) {
    if (proposal.piece == NULL) {
        return false;
    }
    proposal.square = square;
    gameCycle();
    return true;
}

void GameRunner::clearProposal() {
    proposal.piece = NULL;
    proposal.square = NULL;
    proposal.aux.reset();
    proposal.restoration.clear();
    proposal.instr = "";
}

void GameRunner::finishGame() {
    delete game;
}