#ifndef PIECE_PARSER_H
#define PIECE_PARSER_H

class PieceParser;

#include <vector>
#include <string>
#include <map>

class PieceParser {
    public:
        // Constructor with the game name and the input vector of string
        PieceParser(const std::string& gameName, const std::vector <std::string>& input);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
        // get the file name according to gamename and name
        std::string getFileName();
    private:
        // the name of the game
        std::string gameName;
        // the name of the piece
        std::string name;
        // the symbol of the piece
        char symbol;
        // whether the piece is a king
        bool king;
        // the given movements of a piece
        std::vector <std::string> movement;
        // the look up map for moves for WHITE
        std::map <std::string, std::string> moveMapWhite;
        // the look up map for moves for BLACK
        std::map <std::string, std::string> moveMapBlack;
        // set up the moveMap for WHITE
        void setUpMoveMapWhite();
        // set up the moveMap for BLACK
        void setUpMoveMapBlack();
};

#endif