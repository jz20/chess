#include "chessgame.h"

#include <cstddef>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
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
        promoted = new Type(move.square, current); \
        move.square->setPiece(promoted); \
        current->addPiece(promoted);

#define EMPTY_AND_FREE(y, x) \
        (opCtrl.count(board->getSquare(y, x)) == 0) && board->getSquare(y, x)->isEmpty()

#define ADD_CASTLE(king, dKing, oRook, dRook, row) \
        GameMove move; \
        GameMove *aux = new GameMove; \
        move.piece = king; \
        move.square = board->getSquare(row, dKing); \
        aux->piece = board->getSquare(row, oRook)->getPiece(); \
        aux->square = board->getSquare(row, dRook); \
        move.aux.reset(aux); \
        moves.push_back(move);

#define ADD_PROMOTION(name, instruction) \
        GameMove name; \
        name.piece = current.piece; \
        name.square = current.square; \
        name.instr = instruction; \
        temp.push_back(name);

#define ADD_EN_PASSANT(oRow, oCol, dRow) \
        GameMove move; \
        move.piece = board->getSquare(oRow, oCol)->getPiece(); \
        move.square = board->getSquare(dRow, flags.EP_COL); \
        move.instr = "ep"; \
        moves.push_back(move);

#define SET_PIECE(name, y, x, player, Type) \
        Piece *name = new Type(board->getSquare(y, x), player); \
        board->getSquare(y, x)->setPiece(name); \
        player->addPiece(name);
        

#define EPWHITE 4
#define EPBLACK 3
#define WHITE_PAWN_INIT 1
#define BLACK_PAWN_INIT 6
#define WHITE_KING_ROW 0
#define BLACK_KING_ROW 7
#define BOARD_SIZE 8

// Constructor with the board and the players
ChessGame::ChessGame(): Game(new Board(8, 8), new Player(WHITE), new Player(BLACK)) {
}

// Destructor of ChessGame
ChessGame::~ChessGame() {
}

// try the input move, store the move on the stack so that it can be 
// reversed
void ChessGame::tryMove(GameMove& move, bool isAux) {
    if (!isAux) {
        updateFlags(move);
    }
    Player *current = getCurrentPlayer();
    Game::tryMove(move, isAux);
    Piece *promoted = NULL;
    if (move.instr == "ep") {
        int rmRow = (current->getColour() == WHITE) ? EPWHITE : EPBLACK;
        int rmCol = move.square->getCol();
        Square *TPS = board->getSquare(rmRow, rmCol); // TPS = taken pawn square
        Positioning pos{TPS->getPiece(), TPS};
        move.restoration.push_back(pos);
        if (!TPS->isEmpty()) {
            TPS->getPiece()->setSquare(NULL);
        }
        TPS->setEmpty();
    } else if (move.instr == "queen") {
        PROMOTE_TO(Queen);
    } else if (move.instr == "rook") {
        PROMOTE_TO(Rook);
    } else if (move.instr == "bishop") {
        PROMOTE_TO(Bishop);
    } else if (move.instr == "knight") {
        PROMOTE_TO(Knight);
    }
    if (!isAux) {
        storeBoardState();
        Player *opposite = current == player1 ? player2 : player1;
        inCheck = checkTest(opposite);
    }
}

// try the input move, store the move on the stack so that it can be reversed
void ChessGame::tryMove(GameMove& move) {
    ChessGame::tryMove(move, false);
}

// reverse last move on the moveStack, returns false if the moveStack is empty
bool ChessGame::reverseLast() {
    if (!Game::reverseLast()) {
        return false;
    }
    reverseFlags();
    boardStateStack.pop_back();
    return true;
}

// update the moves that a player can make
void ChessGame::updateMoves() {
    moves.clear();
    basicMoves();
    pawnTwoSquare();
    castling();
    enPassant();
    removeIllegalMoves();
    promotion();
}

// set up the pieces for the board and the players
void ChessGame::setUp() {
    flags.WSC = true;
    flags.WLC = true;
    flags.BSC = true;
    flags.BLC = true;
    flags.EP_COL = -1;
    flags.FIFTY = 0;
    flags.REP = 0;
    flagsStack.push_back(flags);

    // pieces
    SET_PIECE(wr1, 0, 0, player1, Rook);
    SET_PIECE(wn1, 0, 1, player1, Knight);
    SET_PIECE(wb1, 0, 2, player1, Bishop);
    SET_PIECE(wq, 0, 3, player1, Queen);
    SET_PIECE(wk, 0, 4, player1, King);
    SET_PIECE(wb2, 0, 5, player1, Bishop);
    SET_PIECE(wn2, 0, 6, player1, Knight);
    SET_PIECE(wr2, 0, 7, player1, Rook);
    SET_PIECE(wp1, 1, 0, player1, Pawn);
    SET_PIECE(wp2, 1, 1, player1, Pawn);
    SET_PIECE(wp3, 1, 2, player1, Pawn);
    SET_PIECE(wp4, 1, 3, player1, Pawn);
    SET_PIECE(wp5, 1, 4, player1, Pawn);
    SET_PIECE(wp6, 1, 5, player1, Pawn);
    SET_PIECE(wp7, 1, 6, player1, Pawn);
    SET_PIECE(wp8, 1, 7, player1, Pawn);
    whiteKing = wk;
    whiteKings.push_back(wk);
    SET_PIECE(br1, 7, 0, player2, Rook);
    SET_PIECE(bn1, 7, 1, player2, Knight);
    SET_PIECE(bb1, 7, 2, player2, Bishop);
    SET_PIECE(bq, 7, 3, player2, Queen);
    SET_PIECE(bk, 7, 4, player2, King);
    SET_PIECE(bb2, 7, 5, player2, Bishop);
    SET_PIECE(bn2, 7, 6, player2, Knight);
    SET_PIECE(br2, 7, 7, player2, Rook);
    SET_PIECE(bp1, 6, 0, player2, Pawn);
    SET_PIECE(bp2, 6, 1, player2, Pawn);
    SET_PIECE(bp3, 6, 2, player2, Pawn);
    SET_PIECE(bp4, 6, 3, player2, Pawn);
    SET_PIECE(bp5, 6, 4, player2, Pawn);
    SET_PIECE(bp6, 6, 5, player2, Pawn);
    SET_PIECE(bp7, 6, 6, player2, Pawn);
    SET_PIECE(bp8, 6, 7, player2, Pawn);
    blackKing = bk;
    blackKings.push_back(bk);
    storeBoardState();
}

// check if the game is over, set finished to be true if so, return
// true if a player wins and false if there is a draw, the result is 
// meaningless unless finished is true
bool ChessGame::checkResult() {
    if (flags.REP >= 3 || flags.FIFTY / 2 >= 50 || insufficientMaterial()) {
        finished = true;
        return false;
    }
    updateMoves();
    if (moves.empty()) {
        finished = true;
        if (checkTest(getCurrentPlayer())) {
            return true;
        }
        return false;
    }
    return true;
}

// update pawns' two-square moves
void ChessGame::pawnTwoSquare() {
    if (getCurrentPlayer()->getColour() == WHITE) {
        int row = WHITE_PAWN_INIT;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (!board->getSquare(row, i)->isEmpty()
                    && board->getSquare(row, i)->getPiece()->getName() == "pawn" 
                    && board->getSquare(row + 1, i)->isEmpty()
                    && board->getSquare(row + 2, i)->isEmpty()) {
                GameMove move;
                move.piece = board->getSquare(row, i)->getPiece();
                move.square = board->getSquare(row + 2, i);
                moves.push_back(move);
            }
        }
    } else {
        int row = BLACK_PAWN_INIT;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (!board->getSquare(row, i)->isEmpty()
                    && board->getSquare(row, i)->getPiece()->getName() == "pawn" 
                    && board->getSquare(row - 1, i)->isEmpty()
                    && board->getSquare(row - 2, i)->isEmpty()) {
                GameMove move;
                move.piece = board->getSquare(row, i)->getPiece();
                move.square = board->getSquare(row - 2, i);
                moves.push_back(move);
            }
        }
    }
}

// update the castling moves
void ChessGame::castling() {
    if (!inCheck) {
        set <Square *> opCtrl = squaresControlled(getOppositePlayer());
        if (getCurrentPlayer()->getColour() == WHITE) {
            if (flags.WLC && EMPTY_AND_FREE(WHITE_KING_ROW, 1) 
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 2)
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 3)) {
                ADD_CASTLE(whiteKing, 2, 0, 3, WHITE_KING_ROW);
            }
            if (flags.WSC && EMPTY_AND_FREE(WHITE_KING_ROW, 5) 
                    && EMPTY_AND_FREE(WHITE_KING_ROW, 6)) {
                ADD_CASTLE(whiteKing, 6, 7, 5, WHITE_KING_ROW);
            }
        } else {
            if (flags.BLC && EMPTY_AND_FREE(BLACK_KING_ROW, 1) 
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 2)
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 3)) {
                ADD_CASTLE(blackKing, 2, 0, 3, BLACK_KING_ROW);
            }
            if (flags.BSC && EMPTY_AND_FREE(BLACK_KING_ROW, 5) 
                    && EMPTY_AND_FREE(BLACK_KING_ROW, 6)) {
                ADD_CASTLE(blackKing, 6, 7, 5, BLACK_KING_ROW);
            }
        }
    }
}

// update the en passant captures
void ChessGame::enPassant() {
    if (flags.EP_COL == -1) {
        return;
    }
    int leftCol = flags.EP_COL - 1;
    int rightCol = flags.EP_COL + 1;
    if (getCurrentPlayer()->getColour() == WHITE) {
        if (leftCol >= 0
                && !board->getSquare(EPWHITE, leftCol)->isEmpty()
                && board->getSquare(EPWHITE, leftCol)->getPiece()->getName() == "pawn"
                && board->getSquare(EPWHITE, leftCol)->getPiece()->getPlayer() == getCurrentPlayer()) {
            ADD_EN_PASSANT(EPWHITE, leftCol, EPWHITE + 1)
        }
        if (rightCol < board->getCols()
                && !board->getSquare(EPWHITE, rightCol)->isEmpty()
                && board->getSquare(EPWHITE, rightCol)->getPiece()->getName() == "pawn"
                && board->getSquare(EPWHITE, rightCol)->getPiece()->getPlayer() == getCurrentPlayer()) {
            ADD_EN_PASSANT(EPWHITE, rightCol, EPWHITE + 1)
        }
    } else {
        if (leftCol >= 0
                && !board->getSquare(EPBLACK, leftCol)->isEmpty()
                && board->getSquare(EPBLACK, leftCol)->getPiece()->getName() == "pawn"
                && board->getSquare(EPBLACK, leftCol)->getPiece()->getPlayer() == getCurrentPlayer()) {
            ADD_EN_PASSANT(EPBLACK, leftCol, EPBLACK - 1)
        }
        if (rightCol < board->getCols()
                && !board->getSquare(EPBLACK, rightCol)->isEmpty()
                && board->getSquare(EPBLACK, rightCol)->getPiece()->getName() == "pawn"
                && board->getSquare(EPBLACK, rightCol)->getPiece()->getPlayer() == getCurrentPlayer()) {
            ADD_EN_PASSANT(EPBLACK, rightCol, EPBLACK - 1)
        }
    }
}

// update the promotion moves
void ChessGame::promotion() {
    vector <GameMove> temp;
    for (vector <GameMove> :: iterator it = moves.begin(); it != moves.end(); ++it) {
        GameMove& current = *it;
        if (getCurrentPlayer()->getColour() == WHITE) {
            if ((current.piece->getName() == "pawn")
                    && (current.square->getRow() == BLACK_KING_ROW)
                    && current.instr == "") {
                current.instr = "queen";
                ADD_PROMOTION(rook, "rook")
                ADD_PROMOTION(bishop, "bishop")
                ADD_PROMOTION(knight, "knight")
            }
        } else {
            if ((current.piece->getName() == "pawn") 
                    && (current.square->getRow() == WHITE_KING_ROW)
                    && current.instr == "") {
                current.instr = "queen";
                ADD_PROMOTION(rook, "rook")
                ADD_PROMOTION(bishop, "bishop")
                ADD_PROMOTION(knight, "knight")
            }
        }
    }
    for (vector <GameMove> :: iterator it = temp.begin(); it != temp.end(); ++it) {
        moves.push_back(*it);
    }
    temp.clear();
}

// update the flags
void ChessGame::updateFlags(GameMove& move) {
    Flags newFlags;
    newFlags.WLC = flags.WLC;
    newFlags.WSC = flags.WSC;
    newFlags.BLC = flags.BLC;
    newFlags.BSC = flags.BSC;
    newFlags.EP_COL = flags.EP_COL;
    newFlags.REP = flags.REP;
    newFlags.FIFTY = flags.FIFTY;
    Piece *piece = move.piece;
    if (piece == whiteKing) {
        newFlags.WLC = false;
        newFlags.WSC = false;
    }
    if (newFlags.WLC
            && piece->getName() == "rook" 
            && piece->getPlayer() == player1
            && piece->getSquare() == board->getSquare(0, 0)) {
        newFlags.WLC = false;
    }
    if (newFlags.WSC 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player1
            && piece->getSquare() == board->getSquare(0, 7)) {
        newFlags.WSC = false;
    }
    if (piece == blackKing) {
        newFlags.BLC = false;
        newFlags.BSC = false;
    }
    if (newFlags.BLC 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player2
            && piece->getSquare() == board->getSquare(7, 0)) {
        newFlags.BLC = false;
    }
    if (newFlags.BSC 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player2
            && piece->getSquare() == board->getSquare(7, 7)) {
        newFlags.BSC = false;
    }
    if (piece->getName() == "pawn"
            && abs(piece->getSquare()->getRow() - move.square->getRow()) == 2) {
        newFlags.EP_COL = piece->getSquare()->getCol();
    } else {
        newFlags.EP_COL = -1;
    }
    if (piece->getName() != "pawn"
            && move.square->getPiece() == NULL) {
        newFlags.FIFTY++;
    } else {
        newFlags.FIFTY = 0;
    }
    flags = newFlags;
    flagsStack.push_back(newFlags);
}

// update trackers
void ChessGame::updateTrackers(GameMove& move) {
    Piece *piece = move.piece;
    if (piece == whiteKing) {
        trackers[WLC] = false;
        trackers[WSC] = false;
    }
    if (trackers[WLC]
            && piece->getName() == "rook" 
            && piece->getPlayer() == player1
            && piece->getSquare() == board->getSquare(0, 0)) {
        trackers[WLC] = false;
    }
    if (trackers[WSC] 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player1
            && piece->getSquare() == board->getSquare(0, 7)) {
        trackers[WSC] = false;
    }
    if (piece == blackKing) {
        trackers[BLC] = false;
        trackers[BSC] = false;
    }
    if (trackers[BLC] 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player2
            && piece->getSquare() == board->getSquare(7, 0)) {
        trackers[BLC] = false;
    }
    if (trackers[BSC] 
            && piece->getName() == "rook" 
            && piece->getPlayer() == player2
            && piece->getSquare() == board->getSquare(7, 7)) {
        trackers[BSC] = false;
    }
    if (piece->getName() == "pawn"
            && abs(piece->getSquare()->getRow() - move.square->getRow()) == 2) {
        trackers[EP_COL] = piece->getSquare()->getCol();
    } else {
        trackers[EP_COL] = -1;
    }
    if (piece->getName() != "pawn"
            && move.square->getPiece() == NULL) {
        trackers[FIFTY]++;
    } else {
        trackers[FIFTY] = 0;
    }
    trackersStack.push_back(trackers);
}

// reverse flags to the previous state
void ChessGame::reverseFlags() {
    flagsStack.pop_back();
    flags = flagsStack.back();
}

// get the pieces that have not been captured, excluding the kings
vector <Piece *> ChessGame::getActivePieces() {
    vector <Piece *> active;
    vector <Piece *> p1 = player1->getPieces();
    vector <Piece *> p2 = player2->getPieces();
    Piece *current = NULL;
    for (vector <Piece *> :: iterator it = p1.begin(); it != p1.end(); it++) {
        current = *it;
        if (current->getSquare() != NULL && current != whiteKing) {
            active.push_back(current);
        }
    }
    for (vector <Piece *> :: iterator it = p2.begin(); it != p2.end(); it++) {
        current = *it;
        if (current->getSquare() != NULL && current != blackKing) {
            active.push_back(current);
        }
    }
    return active;
}

// check if there is insufficient material on the board such that
// there would be a draw, if so return true
bool ChessGame::insufficientMaterial() {
    vector <Piece *> active = getActivePieces();
    if (active.size() == 0) {
        // K v K
        return true;
    } else if (active.size() == 1) {
        if (active.back()->getName() == "bishop" 
                || active.back()->getName() == "knight") {
            // K v KB or K v KN
            return true;
        }
    } else if (active.size() == 2) {
        Piece *ap1 = active.back();
        active.pop_back();
        Piece *ap2 = active.back();
        if (ap1->getName() == "bishop" && ap2->getName() == "bishop"
                && ap1->getPlayer() != ap2->getPlayer()) {
            Square *sq1 = ap1->getSquare();
            Square *sq2 = ap2->getSquare();
            // same coloured bishops
            int oddCount = 0;
            if (sq1->getRow() % 2 == 1) {
                oddCount++;
            }
            if (sq1->getCol() % 2 == 1) {
                oddCount++;
            }
            if (sq2->getRow() % 2 == 1) {
                oddCount++;
            }
            if (sq2->getCol() % 2 == 1) {
                oddCount++;
            }
            if (oddCount % 2 == 0) {
                return true;
            }
        }
    }
    return false;
}

// store the board state into the stack
void ChessGame::storeBoardState() {
    Game::storeBoardState();
    // 3-fold repetition rule
    string snapshot = board->snapshot();
    int count = 0;
    for (vector <string> :: iterator it = boardStateStack.begin(); 
            it != boardStateStack.end(); it++) {
        if (*it == snapshot) {
            count++;
        }
    }
    if (count > flags.REP) {
        flags.REP = count;
    }
}