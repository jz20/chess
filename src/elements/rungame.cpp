#include "rungame.h"
#include "game.h"
#include "chessgame.h"
#include <vector>
#include <iostream>

#define WHITE_KING_ROW 0
#define BLACK_KING_ROW 7

using namespace std;

int main() {
    Game *game = new ChessGame();
    game->setUp();
    vector <Move *> moves;
    Move *move = NULL;
    bool result;
    while (!game->isFinished()) {
        cout << *(game->getBoard());
        game->updateMoves();
        move = inputMove(game);
        game->tryMove(move);
        result = game->checkResult();
    }
    displayResult(game, result);
    return 0;
}

// get input move from cli
Move *inputMove(Game *game) {
    std::vector <Move *> moves = game->getMoves();
    bool available = false;
    Move *move = NULL;
    int oRow = -1;
    int oCol = -1; 
    int dRow = -1;
    int dCol = -1;
    bool promotion = false;
    string promoteTo = "";
    Board *board = game->getBoard();
    while (!available) {
        cout << "Input move origin row:\n";
        cin >> oRow;
        cout << "Input move origin col:\n";
        cin >> oCol;
        cout << "Input move destination row:\n";
        cin >> dRow;
        cout << "Input move destination col:\n";
        cin >> dCol;
        if (!(oRow >= 0 && oRow < board->getRows()
                && oCol >= 0 && oCol < board->getCols()
                && dRow >= 0 && dRow < board->getRows()
                && dCol >= 0 && dCol < board->getCols())
                || board->getSquare(oRow, oCol)->isEmpty()) {
            cout << "Move unavalible\n";
            continue;
        }
        if ((game->getCurrentPlayer()->getColour() == WHITE 
                && board->getSquare(oRow, oCol)->getPiece()->getName() == "pawn"
                && dRow == BLACK_KING_ROW)
                || (game->getCurrentPlayer()->getColour() == BLACK 
                && board->getSquare(oRow, oCol)->getPiece()->getName() == "pawn"
                && dRow == WHITE_KING_ROW)) {
            promotion = true;
            cout << "Promote to: \n";
            cin >> promoteTo;
        }
        for (vector <Move *> :: iterator it = moves.begin(); it != moves.end(); it++) {
            move = *it;
            if (move->piece == board->getSquare(oRow, oCol)->getPiece()
                    && move->square->getRow() == dRow && move->square->getCol() == dCol) {
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
        cout << "Move unavalible\n";
    }
    return move;
}

// display the result of the game
void displayResult(Game *game, bool result) {
    if (result) {
        if (game->getCurrentPlayer()->getColour() == WHITE) {
            cout << "Game over. Black won.\n";
        } else {
            cout << "Game over. White won.\n";
        }
    } else {
        cout << "Game over. Draw.\n";
    }
}