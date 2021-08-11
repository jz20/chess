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
#include "chesssquarepanel.h"
#include "chesspiecebitmap.h"

using namespace std;


bool ChessGameRunner::OnInit() {
    wxInitAllImageHandlers();
    game = new ChessGame();
    frame = new ChessGameFrame("Chess Game", game, this);
    game->setUp();
    frame->updatePieces();
    frame->Show(true);
    thread t(&ChessGameRunner::gameCycle, this);
    t.detach();
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

void ChessGameRunner::gameCycle() {
    vector <GameMove *> moves;
    GameMove *move = NULL;
    bool result;
    while (!game->isFinished()) {
        cout << *(game->getBoard()) << "\n";
        game->updateMoves();
        while (move == NULL) {
            while (proposal.piece == NULL || proposal.square == NULL) {
                // cout << (proposal.piece == NULL) << " TEST3\n";
                this_thread::sleep_for(chrono::milliseconds(10));
            }
            move = actualMove();
            if (move == NULL) {
                clearProposal();
            }
        }
        game->tryMove(move);
        frame->updatePieces();
        move = NULL;
        result = game->checkResult();
    }
}

void ChessGameRunner::waitForInput() {

}

void ChessGameFrame::updatePieces() {
    int count = 0;
    int row = 0;
    int col = 0;
    Board *board = game->getBoard();
    cout << pSquares.size() << "\n";
    for (vector <wxStaticBitmap *> :: iterator it = bPieces.begin(); it != bPieces.end(); it++) {
        // cout << count << "\n";
        (*it)->Hide();
        (*it)->Close();
        // count++;
    }
    bPieces.clear();
    count = 0;
    for (vector <wxPanel *> :: iterator it = pSquares.begin(); it != pSquares.end(); it++) {
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
                    wxPoint(0,0), wxSize(squareSize, squareSize), 0, piece->getSquare(), runner);
            bPieces.push_back(img);
            // (*it)->AddChild(img);
            // pieceMap[*it] = img;
            // cout << (img == pieceMap[*it]) << "\n";
            // pieceMap[*it]->Destroy();
        }
        count++;
    }
}

// get the actual move
GameMove *ChessGameRunner::actualMove() {
    GameMove *move;
    vector <GameMove *> moves = game->getMoves();
    bool promotion = false;
    string promoteTo = "";
    for (vector <GameMove *> :: iterator it = moves.begin(); it != moves.end(); it++) {
        move = *it;
        if (move->piece == (proposal.piece)
                && move->square == (proposal.square)) {
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
bool ChessGameRunner::input(Square *square) {
    if (proposal.piece == NULL && square->getPiece() != NULL) {
        return inputPiece(square->getPiece());
    } else {
        return inputSquare(square);
    }
}

// input the move piece in the proposal move
bool ChessGameRunner::inputPiece(Piece *piece) {
    proposal.piece = piece;
    cout << "P\n";
    return true;
}

// input the move square in the proposal move
bool ChessGameRunner::inputSquare(Square *square) {
    if (proposal.piece == NULL) {
        return false;
    }
    cout << "S\n";
    proposal.square = square;
    return true;
}

void ChessGameRunner::clearProposal() {
    proposal.piece = NULL;
    proposal.square = NULL;
    delete proposal.aux;
    proposal.aux = NULL;
    proposal.restoration.clear();
    proposal.instr = "";
}
