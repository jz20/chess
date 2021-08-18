#ifndef RUN_GAME_H
#define RUN_GAME_H

#include <vector>
#include "game.h"

// program entry
int main();

// get input move from cli
GameMove inputMove(Game *game);

// display the result of the game
void displayResult(Game *game, bool result);

#endif