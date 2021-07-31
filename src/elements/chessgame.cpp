#include "chessgame.h"

#include <cstddef>
#include <vector>
#include <set>
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

/*
#define PROMOTE_TO(Type) \
        getCurrentPlayer()->removePiece(move->piece); 
        promoted = new Type(move->square, getCurrentPlayer()); \
        move->square->setPiece(promoted); \
        getCurrentPlayer()->addPiece(promoted);
        */

#define PROMOTE_TO(Type) \
        promoted = new Type(move->square, getCurrentPlayer()); \
        move->square->setPiece(promoted); \
        getCurrentPlayer()->addPiece(promoted);

#define EMPTY_AND_FREE(y, x) \
        (opCtrl.count(board->getSquare(y, x)) == 0) && board->getSquare(y, x)->isEmpty()

#define ADD_PROMOTION(name, instruction) \
        Move name; \
        name.piece = current->piece; \
        name.square = current->square; \
        name.instr = instruction; \
        moves.push_back(&name);
        

#define EPWHITE 4
#define EPBLACK 3
#define WHITE_PAWN_INIT 1
#define BLACK_PAWN_INIT 6
#define WHITE_KING_ROW 0
#define BLACK_KING_ROW 7
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

// make the input move, including the possible promotion of a pawn and en 
// passant pawn capture, return false if the moveStack is empty thus the move
// cannot be made
bool ChessGame::makeMove(Move *move) {
    if (!moveStack.empty()) {
        return false;
    }
    Game::makeMove(move);
    Piece *promoted = NULL;
    if (move->instr == "ep") {
        int rmRow = (getCurrentPlayer()->getColour() == WHITE) ? EPWHITE : EPBLACK;
        int rmCol = move->square->getCol();
        getOppositePlayer()->removePiece(board->getSquare(rmRow, rmCol)->getPiece());
    } else if (move->instr == "queen") {
        PROMOTE_TO(Queen);
    } else if (move->instr == "rook") {
        PROMOTE_TO(Rook);
    } else if (move->instr == "bishop") {
        PROMOTE_TO(Bishop);
    } else if (move->instr == "knight") {
        PROMOTE_TO(Knight);
    }
    if (move->aux) {
        Game::makeMove(move->aux);
    }
    return true;
}

// try the input move, store the move on the stack so that it can be 
// reversed
void ChessGame::tryMove(Move *move, bool isAux) {
    Game::tryMove(move, isAux);
    Piece *promoted = NULL;
    if (move->instr == "ep") {
        int rmRow = (getCurrentPlayer()->getColour() == WHITE) ? EPWHITE : EPBLACK;
        int rmCol = move->square->getCol();
        Square *TPS = board->getSquare(rmRow, rmCol); // TPS = taken pawn square
        Positioning pos = {TPS->getPiece(), TPS};
        move->restoration.push_back(&pos);
        TPS->getPiece()->setSquare(NULL);
        TPS->setEmpty();
    } else if (move->instr == "queen") {
        PROMOTE_TO(Queen);
    } else if (move->instr == "rook") {
        PROMOTE_TO(Rook);
    } else if (move->instr == "bishop") {
        PROMOTE_TO(Bishop);
    } else if (move->instr == "knight") {
        PROMOTE_TO(Knight);
    }
}

// update the moves that a player can make
void ChessGame::updateMoves() {
    set <Square *> opponentControlled = squaresControlled(getOppositePlayer());
    basicMoves();
    pawnTwoSquare();
    castling(opponentControlled);
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

// update the castling moves
void ChessGame::castling(set <Square *> opCtrl) {
    if (!inCheck) {
        Move move;
        Move aux;
        if (getCurrentPlayer()->getColour() == WHITE) {
            move.piece = board->getSquare(WHITE_KING_ROW, 4)->getPiece();
            if (WLC && EMPTY_AND_FREE(WHITE_KING_ROW, 1) 
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 2)
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 3)) {
                move.square = board->getSquare(WHITE_KING_ROW, 2);
                aux.piece = board->getSquare(WHITE_KING_ROW, 0)->getPiece();
                aux.square = board->getSquare(WHITE_KING_ROW, 3);
            }
            if (WSC && EMPTY_AND_FREE(WHITE_KING_ROW, 5) 
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 6)) {
                move.square = board->getSquare(WHITE_KING_ROW, 6);
                aux.piece = board->getSquare(WHITE_KING_ROW, 7)->getPiece();
                aux.square = board->getSquare(WHITE_KING_ROW, 5);
            }
        } else {
            if (BLC && EMPTY_AND_FREE(BLACK_KING_ROW, 1) 
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 2)
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 3)) {
                move.square = board->getSquare(BLACK_KING_ROW, 2);
                aux.piece = board->getSquare(BLACK_KING_ROW, 0)->getPiece();
                aux.square = board->getSquare(BLACK_KING_ROW, 3);
            }
            if (BSC && EMPTY_AND_FREE(BLACK_KING_ROW, 5) 
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 6)) {
                move.square = board->getSquare(BLACK_KING_ROW, 6);
                aux.piece = board->getSquare(BLACK_KING_ROW, 7)->getPiece();
                aux.square = board->getSquare(BLACK_KING_ROW, 5);
            }
        }
        move.aux = &aux;
        moves.push_back(&move);
    }
}

// update the en passant captures
void ChessGame::enPassant() {
    int leftCol = EP_COL - 1;
    int rightCol = EP_COL + 1;
    if (getCurrentPlayer()->getColour() == WHITE) {
        if (leftCol >= 0) {
            if (board->getSquare(EPWHITE, leftCol)->getPiece()->getName() == "pawn") {
                Move move;
                move.piece = board->getSquare(EPWHITE, leftCol)->getPiece();
                move.square = board->getSquare(EPWHITE + 1, EP_COL);
                move.instr = "ep";
            }
        }
        if (rightCol < board->getCols()) {
            if (board->getSquare(EPWHITE, rightCol)->getPiece()->getName() == "pawn") {
                Move move;
                move.piece = board->getSquare(EPWHITE, rightCol)->getPiece();
                move.square = board->getSquare(EPWHITE + 1, EP_COL);
                move.instr = "ep";
            }
        }
    } else {
        if (leftCol >= 0) {
            if (board->getSquare(EPBLACK, leftCol)->getPiece()->getName() == "pawn") {
                Move move;
                move.piece = board->getSquare(EPBLACK, leftCol)->getPiece();
                move.square = board->getSquare(EPBLACK - 1, EP_COL);
                move.instr = "ep";
            }
        }
        if (rightCol < board->getCols()) {
            if (board->getSquare(EPBLACK, rightCol)->getPiece()->getName() == "pawn") {
                Move move;
                move.piece = board->getSquare(EPBLACK, rightCol)->getPiece();
                move.square = board->getSquare(EPBLACK - 1, EP_COL);
                move.instr = "ep";
            }
        }
    }
}

// update the promotion moves
void ChessGame::promotion() {
    Move *current = NULL;
    for (vector <Move *> :: iterator it = moves.begin(); it != moves.end(); ++it) {
        current = *it;
        if (getCurrentPlayer()->getColour() == WHITE) {
            if ((current->piece->getName() == "pawn") 
                    && (current->square->getRow() == BLACK_KING_ROW)) {
                current->instr = "queen";
                ADD_PROMOTION(rook, "rook")
                ADD_PROMOTION(bishop, "bishop")
                ADD_PROMOTION(knight, "knight")
            }
        } else {
            if ((current->piece->getName() == "pawn") 
                    && (current->square->getRow() == WHITE_KING_ROW)) {
                current->instr = "queen";
                ADD_PROMOTION(rook, "rook")
                ADD_PROMOTION(bishop, "bishop")
                ADD_PROMOTION(knight, "knight")
            }
        }
    }
}

// get the squares that are controlled by a player
set <Square *> ChessGame::squaresControlled(Player* player) {
    vector <Piece *> pieces = player->getPieces();
    set <Square *> squareSet;
    Piece *current = NULL;
    for (vector <Piece *> :: iterator it = pieces.begin(); it != pieces.end(); ++it) {
        current = *it;
        current->updateTargets();
        vector <Square *> currentTargets = current->getTargets();
        copy(currentTargets.begin(), currentTargets.end(),
                inserter(squareSet, squareSet.end()));
    }
    return squareSet;
}
