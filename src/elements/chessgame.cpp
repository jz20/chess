#include "chessgame.h"

#include <cstddef>
#include <vector>
#include <string>
#include "piece.h"
#include "square.h"

#include "cpbishop.h"
#include "cpknight.h"
#include "cprook.h"
#include "cpking.h"
#include "cpqueen.h"
#include "cppawn.h"

using namespace std;

#define PROMOTE_TO(Type) \
        promoted = new Type(move->square, getCurrentPlayer()); \
        move->square->setPiece(promoted); \
        getCurrentPlayer()->addPiece(promoted);

#define EPWHITE 4
#define EPBLACK 3
#define WHITE_PAWN_INIT 1
#define BLACK_PAWN_INIT 6
#define BOARD_SIZE 8

// Constructor with the board and the players
ChessGame::ChessGame(): Game(new Board(8, 8), new Player(WHITE), new Player(BLACK)) {
    WSC = true;
    WLC = true;
    BSC = true;
    BLC = true;
    EP_COL = -1;
}

// Destructor of ChessGame
ChessGame::~ChessGame() {
}

// make the input move, including the possible promotion of a pawn and en passant
// pawn capture
void ChessGame::makeMove(Move *move, Castle castle, Promotion promotion, bool enPassant) {
    Game::makeMove(move);
    if (castle.happens) {
        Game::makeMove(castle.rookMove);
    } else {
        if (enPassant) {
            int row = (getCurrentPlayer()->getColour() == WHITE) ? EPWHITE : EPBLACK;
            int col = move->square->getCol();
            getOppositePlayer()->removePiece(board->getSquare(row, col)->getPiece());
        } else {
            getCurrentPlayer()->removePiece(move->piece);
            Piece *promoted;
            switch (promotion) {
                case NA:
                    break;
                case QUEEN:
                    PROMOTE_TO(Queen);
                    break;
                case ROOK:
                    PROMOTE_TO(Rook);
                    break;
                case BISHOP:
                    PROMOTE_TO(Bishop);
                    break;
                case KNIGHT:
                    PROMOTE_TO(Knight);
                    break;
                default:
                    break;
            }
        }
    }
}

// update the moves that a player can make
void ChessGame::updateMoves() {
    basicMoves();
    pawnTwoSquare();
}

// update the basic moves (the moves that are determined by the usual move 
// rules for each piece)
void ChessGame::basicMoves() {
    vector <Piece *> pieces = getCurrentPlayer()->getPieces();
    Piece *current = NULL;
    for (vector <Piece *> :: iterator it1 = pieces.begin(); it1 != pieces.end(); ++it1) {
        current = *it1;
        current->updateTargets();
        vector <Square *> targets = current->getTargets();
        for (vector <Square *> :: iterator it2 = targets.begin(); it2 != targets.end(); ++it2) {
            Move move;
            move.piece = current;
            move.square = *it2;
            moves.push_back(&move);
        }
    }
}

// update pawns' two-square moves

void ChessGame::pawnTwoSquare() {
    if (getCurrentPlayer()->getColour() == WHITE) {
        int row = WHITE_PAWN_INIT;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board->getSquare(row, i)->getPiece()->getName() == "pawn" 
                    && board->getSquare(row + 1, i)->isEmpty()
                    && board->getSquare(row + 2, i)->isEmpty()) {
                Move move;
                move.piece = board->getSquare(row, i)->getPiece();
                move.square = board->getSquare(row + 2, i);
                moves.push_back(&move);
            }
        }
    } else {
        int row = BLACK_PAWN_INIT;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board->getSquare(row, i)->getPiece()->getName() == "pawn" 
                    && board->getSquare(row - 1, i)->isEmpty()
                    && board->getSquare(row - 2, i)->isEmpty()) {
                Move move;
                move.piece = board->getSquare(row, i)->getPiece();
                move.square = board->getSquare(row - 2, i);
                moves.push_back(&move);
            }
        }
    }
}
