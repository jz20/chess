#ifndef GAME_PARSER_H
#define GAME_PARSER_H

class GameParser;

#include <vector>
#include <string>
#include "pieceparser.h"

class GameParser {
    public:
        // constructor with the vector of string input
        GameParser(std::vector <std::string>& input);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
        // produce the content of the make file in the form of a vector of strings
        std::vector <std::string> makeFile();
    private:
        // number of rows
        int rows;
        // number of cols
        int cols;
        // the content of the game
        std::vector <std::string> instr;
        // the name of the game
        std::string name;
        // the piece definitions
        std::vector <std::vector <std::string>> pieceDefs;
        // the piece parsers
        std::vector <PieceParser> pieceParsers;
        // the move definitions
        std::vector <std::vector <std::string>> moves;
        // the promotion definitions
        std::vector <std::vector <std::string>> promotions;
        // the pre-move updates
        std::vector <std::vector <std::string>> premoveUpdates;
        // the pre-move updates
        std::vector <std::vector <std::string>> postmoveUpdates;
        // the trackers
        std::vector <std::string> trackers;
        // the board setup
        std::vector <std::string> setup;
        // the win conditions
        std::vector <std::string> winConds;
        // the draw conditions
        std::vector <std::string> drawConds;
};

#endif