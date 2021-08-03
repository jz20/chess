#include "game.h"
#include "chessgame.h"
#include <vector>
#include <iostream>

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
        moves = game->getMoves();
        move = NULL; // TODO
        game->tryMove(move);
        game->checkResult();
    }
    if (result) {
        // oppo wins
    } else {
        // draw
    }
    return 0;
}