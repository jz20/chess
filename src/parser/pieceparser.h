#ifndef PIECE_PARSER_H
#define PIECE_PARSER_H

class PieceParser;

#include <vector>
#include <string>

class PieceParser {
    public:
        // Constructor with the game name and the input vector of string
        PieceParser(const std::string& gameName, const std::vector <std::string>& input);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
    private:
        // the name of the game
        std::string gameName;
        // the name of the piece
        std::string name;
        // the symbol of the piece
        std::string symbol;
        // whether the piece is a king
        bool king;
        // the given movements of a piece
        std::vector <std::string> movement;
        
};

#endif