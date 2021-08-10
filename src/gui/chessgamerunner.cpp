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
#include <game.h>
#include <chessgame.h>
#include <thread>
#include "chesssquarepanel.h"
#include "chesspiecebitmap.h"

using namespace std;


bool ChessGameRunner::OnInit() {
    wxInitAllImageHandlers();
    game = new ChessGame();
    ChessGameFrame *frame = new ChessGameFrame("Chess Game", game, this);
    game->setUp();
    vector <GameMove *> moves;
    GameMove *move = NULL;
    bool result;
    frame->Show(true);
    frame->updatePieces();
    cout << "TEST\n";
    // thread t(test);
    // t.detach();
    /*
    while (!game->isFinished()) {
        frame->updatePieces();
        game->updateMoves();
        while (proposal.piece == NULL || proposal.square == NULL) {
            // move = actualMove();
        }
        game->tryMove(move);
        result = game->checkResult();
    }
    */
    

    return true;
}

wxIMPLEMENT_APP(ChessGameRunner);

//wxFrame(NULL, wxID_ANY, title, pos, size)
ChessGameFrame::ChessGameFrame(const wxString title, Game* game, ChessGameRunner *runner) {
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
            wxPanel* pSquare = new ChessSquarePanel(pBoard, id, wxPoint(xPos, yPos),
                    wxSize(squareSize, squareSize), board->getSquare(i, j), runner);
            if ((i + j) % 2 == 0) {
                pSquare->SetBackgroundColour(light);
            } else {
                pSquare->SetBackgroundColour(dark);
            }
            // pSquare->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(&ChessGameFrame::test), NULL, this);
            // Connect(id, );
            // Bind();
            pSquares.push_back(pSquare);
            xPos += squareSize;
        }
        xPos = 0;
        yPos -= squareSize;
    }
    FitInside();
}

// get pointer to proposal move
GameMove *ChessGameRunner::ptrProposal() {
    return &proposal;
}

void ChessGameFrame::updatePieces() {
    int count = 0;
    int row = 0;
    int col = 0;
    Board *board = game->getBoard();
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
        if (pieceMap[*it] != NULL) {
            pieceMap[*it]->Destroy();
        }
        row = count / 8;
        col = count % 8;
        Piece *piece = board->getSquare(row, col)->getPiece();
        if (piece != NULL) {
            wxString path = "../../img/chess/";
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
            wxStaticBitmap *img; 
            img = new ChessPieceBitmap(*it, wxNewId(), 
            wxBitmap(wxImage(path).Rescale(squareSize, squareSize)),
                    wxPoint(0,0), wxSize(squareSize, squareSize), 0);
            pieceMap[*it] = img;
        }
        count++;
    }
}

// get the actual move
GameMove *ChessGameRunner::actualMove(GameMove *prop) {
    GameMove *move;
    vector <GameMove *> moves = game->getMoves();
    bool promotion = false;
    string promoteTo = "";
    for (vector <GameMove *> :: iterator it = moves.begin(); it != moves.end(); it++) {
        move = *it;
        if (move->piece == (prop->piece)
                && move->square == (prop->square)) {
            if (promotion) {
                if (move->instr == promoteTo) {
                    return move;
                }
                promotion = false;
            } else {
                return move;
            }
        }
    }
    return NULL;
}

// input raw row and col values, call inputPiece or inputRow accordingly
bool ChessGameRunner::input(int row, int col) {
    cout << row << ", " << col << "\n";
    return true;
    /*
    if (proposal.piece == NULL) {
        return inputPiece(row, col);
    } else {
        inputSquare(row, col);
        return true;
    }
    */
}

// input the move piece in the proposal move
bool ChessGameRunner::inputPiece(int row, int col) {
    Board *board = game->getBoard();
    if (board->getSquare(row, col)->getPiece() == NULL) {
        return false;
    }
    proposal.piece = board->getSquare(row, col)->getPiece();
    return true;
}

// input the move square in the proposal move
void ChessGameRunner::inputSquare(int row, int col) {
    Board *board = game->getBoard();
    proposal.square = board->getSquare(row, col);
}

void ChessGameRunner::clearMove() {
    proposal.piece = NULL;
    proposal.square = NULL;
    delete proposal.aux;
    proposal.aux = NULL;
    proposal.restoration.clear();
    proposal.instr = "";
}
