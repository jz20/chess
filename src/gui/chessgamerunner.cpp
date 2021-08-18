#include "chessgamerunner.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/wfstream.h>
#include <wx/bitmap.h>
#include <vector>
#include <cstddef>
#include <string>
#include "game.h"
#include "chessgame.h"
#include <thread>
#include <chrono>
#include "chesspiecebitmap.h"

using namespace std;

#define WHITE_KING_ROW 0
#define BLACK_KING_ROW 7

bool ChessGameRunner::OnInit() {
    wxInitAllImageHandlers();
    game = new ChessGame();
    frame = new ChessGameFrame("Chess Game", game, this);
    game->setUp();
    frame->updatePieces();
    frame->Show(true);
    /*
    thread *t = new thread(&ChessGameRunner::gameCycle, this);
    t->detach();
    */
    return true;
}

wxIMPLEMENT_APP(ChessGameRunner);

//wxFrame(NULL, wxID_ANY, title, pos, size)
ChessGameFrame::ChessGameFrame(const wxString title, Game* game, ChessGameRunner *runner) {
    Connect(wxEVT_CLOSE_WINDOW, wxCommandEventHandler(ChessGameFrame::onClose), NULL, this);
    this->runner = runner;
    this->game = game;
    squareSize = 64;
    Board *board = game->getBoard();
    int rows = board->getRows();
    int cols = board->getCols();
    int xPos = 0;
    int yPos = (rows - 1) * squareSize;
    int extra = 50;
    wxColour light = wxColour(240,176,87);
    wxColour dark = wxColour(137,82,23);
    Create(0, wxID_ANY, title, wxPoint(0, 0), wxSize(rows * squareSize, cols * squareSize + extra), wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    pBoard = new wxPanel(this, wxNewId(), wxPoint(0, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            wxWindowID id = wxNewId();
            wxPanel* pSquare = new wxPanel(pBoard, id, wxPoint(xPos, yPos),
                    wxSize(squareSize, squareSize));
            if ((i + j) % 2 == 0) {
                pSquare->SetBackgroundColour(light);
            } else {
                pSquare->SetBackgroundColour(dark);
            }
            pSquares.push_back(pSquare);
            ChessPieceBitmap *img;
            wxString path = "../../img/chess/empty.png";
            img = new ChessPieceBitmap(pSquare, wxNewId(), 
            wxBitmap(wxImage(path).Rescale(squareSize, squareSize)),
                    wxPoint(0, 0), wxSize(squareSize, squareSize), 0, board->getSquare(i, j), runner);
            pieceMap[pSquare] = img;
            xPos += squareSize;
        }
        xPos = 0;
        yPos -= squareSize;
    }
    FitInside();
    updatePieces();
}

void ChessGameRunner::gameCycle() {
    game->updateMoves();
    GameMove move = actualMove();
    if (move.instr != "unavailable") {
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

void ChessGameRunner::finishGame() {
    delete game;
}

void ChessGameFrame::updatePieces() {
    int count = 0;
    int row = 0;
    int col = 0;
    Board *board = game->getBoard();
    count = 0;
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
        row = count / 8;
        col = count % 8;
        Piece *piece = board->getSquare(row, col)->getPiece();
        wxString path = "../../img/chess/";
        if (piece != NULL) {
            if (piece->getPlayer()->getColour() == WHITE) {
                if (piece->getName() == "king") {
                    path += "white_king.png";
                } else if (piece->getName() == "queen") {
                    path += "white_queen.png";
                } else if (piece->getName() == "rook") {
                    path += "white_rook.png";
                } else if (piece->getName() == "bishop") {
                    path += "white_bishop.png";
                } else if (piece->getName() == "knight") {
                    path += "white_knight.png";
                } else if (piece->getName() == "pawn") {
                    path += "white_pawn.png";
                }
            } else {
                if (piece->getName() == "king") {
                    path += "black_king.png";
                } else if (piece->getName() == "queen") {
                    path += "black_queen.png";
                } else if (piece->getName() == "rook") {
                    path += "black_rook.png";
                } else if (piece->getName() == "bishop") {
                    path += "black_bishop.png";
                } else if (piece->getName() == "knight") {
                    path += "black_knight.png";
                } else if (piece->getName() == "pawn") {
                    path += "black_pawn.png";
                }
            }
        } else {
            path += "empty.png";
        }
        pieceMap[*it]->SetBitmap(wxBitmap(wxImage(path).Rescale(squareSize, squareSize)));
        count++;
    }
}

// get the actual move
GameMove ChessGameRunner::actualMove() {
    GameMove move;
    vector <GameMove> moves = game->getMoves();
    bool promotion = false;
    string promoteTo = "queen";
        if ((game->getCurrentPlayer()->getColour() == WHITE 
                && proposal.piece->getName() == "pawn"
                && proposal.square->getRow() == BLACK_KING_ROW)
                || (game->getCurrentPlayer()->getColour() == BLACK 
                && proposal.piece->getName() == "pawn"
                && proposal.square->getRow() == WHITE_KING_ROW)) {
            promotion = true;
            cout << "promotion\n";
            wxArrayString choices;
            choices.Add(wxT("queen"));
            choices.Add(wxT("rook"));
            choices.Add(wxT("bishop"));
            choices.Add(wxT("knight"));
            wxSingleChoiceDialog *dial = new wxSingleChoiceDialog(NULL, 
                    wxT("Choose a piece to promote to:"), wxT("Promotion"), choices);
            dial->ShowModal();
            switch (dial->GetSelection()) {
                case 1:
                    promoteTo = "rook";
                    break;
                case 2:
                    promoteTo = "bishop";
                    break;
                case 3:
                    promoteTo = "knight";
                    break;
                case 0:
                default:
                    promoteTo = "queen";
                    break;
            }
        }
    for (vector <GameMove> :: iterator it = moves.begin(); it != moves.end(); it++) {
        move = *it;
        if (move.piece == (proposal.piece)
                && move.square == (proposal.square)) {
            if (promotion) {
                if (move.instr == promoteTo) {
                    promotion = false;
                    string promoteTo = "queen";
                    return move;
                }
            } else {
                return move;
            }
        }
    }
    move.instr = "unavailable";
    return move;
}

// input raw row and col values, call inputPiece or inputRow accordingly
bool ChessGameRunner::input(Square *square) {
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
bool ChessGameRunner::inputPiece(Piece *piece) {
    proposal.piece = piece;
    return true;
}

// input the move square in the proposal move
bool ChessGameRunner::inputSquare(Square *square) {
    if (proposal.piece == NULL) {
        return false;
    }
    proposal.square = square;
    gameCycle();
    return true;
}

void ChessGameRunner::clearProposal() {
    proposal.piece = NULL;
    proposal.square = NULL;
    proposal.aux.reset();
    proposal.restoration.clear();
    proposal.instr = "";
}

// called when the window closes
void ChessGameFrame::onClose(wxCommandEvent& event) {
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
        if (pieceMap.count(*it) > 0 && pieceMap[*it]) {
            delete pieceMap[*it];
        }
        delete *it;
    }
    pSquares.clear();
    runner->finishGame();
    Destroy();
}
