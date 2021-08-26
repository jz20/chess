#ifndef GAME_PARSER_H
#define GAME_PARSER_H

class GameParser;

#include <vector>
#include <string>
#include <unordered_map>
#include "pieceparser.h"
#include "moveparser.h"
#include "promotionparser.h"
#include "trackerupdateparser.h"

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
        // get name
        std::string getName();
        // get the name that the file should have without extension
        std::string getFileName();
        // get the pointer to the vector of piece parsers
        std::vector <PieceParser> *getReferenceToPieceParsers();
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
        // the pieces' names
        std::vector <std::string> pieces;
        // the move definitions
        std::vector <std::vector <std::string>> moveDefs;
        // the move parsers
        std::vector <MoveParser> moveParsers;
        // the promotion definitions
        std::vector <std::vector <std::string>> promotionDefs;
        // the promotion parsers
        std::vector <PromotionParser> promotionParsers;
        // the pre-move updates
        std::vector <std::vector <std::string>> preMoveDefs;
        // the pre-move update parsers
        std::vector <TrackerUpdateParser> preMoveParsers;
        // the post-move updates
        std::vector <std::vector <std::string>> postMoveDefs;
        // the post-move update parsers
        std::vector <TrackerUpdateParser> postMoveParsers;
        // the tracker definitions
        std::vector <std::string> trackerDefs;
        // the trackers
        std::vector <std::string> trackers;
        // the initial value of each tracker
        std::unordered_map <std::string, std::string> trackerValues;
        // the board setup
        std::vector <std::string> setup;
        // the win conditions
        std::vector <std::string> winConds;
        // the draw conditions
        std::vector <std::string> drawConds;
};

#endif