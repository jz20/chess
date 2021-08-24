#ifndef MOVE_PARSER_H
#define MOVE_PARSER_H

class MoveParser;

typedef enum {MIRROR, WHITE, BLACK} MovePlayer;

#include <string>
#include <vector>

class MoveParser {
    public:
        // the constructor with the input
        MoveParser(const std::string gameName, std::vector <std::string>& input, 
            std::vector <std::string>& pieces, std::vector <std::string>& trackers);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
    private:
        // the name of the game
        std::string gameName;
        // the name of the special move
        std::string name;
        // the number of rows in the board
        // int rows; useful for mirror moves implementation
        
        // the player that the move applies to
        MovePlayer movePlayer;
        // whether the move applies to each of a type of pieces
        bool eachPiece;
        // in the case eachPiece is true, the name of the piece
        std::string pieceName;
        // the content of the move
        std::vector <std::string> instr;
        // the name of the pieces
        std::vector <std::string> pieces; // not used currently, may be useful later
        // the name of the trackers
        std::vector <std::string> trackers; // not used currently, may be useful later
        // the aux moves
        std::vector <std::vector <std::string>> auxMoves;
        // the conditions
        std::vector <std::string> conds;
        // the or-conditions
        std::vector <std::vector <std::string>> orConds;
        // the origin
        std::string origin;
        // the destination
        std::string destination;
        // process the origin
        void processOrigin(std::string& ori);
        // process the destination
        void processDestination(std::string& des);
        // process a condition
        std::string processCond(const std::string& cond);
        // process an or-condition
        std::string processOrCond(std::vector <std::string>& cond);
};

#endif