#ifndef GUI_PARSER_H
#define GUI_PARSER_H

class GUIParser;

#include <string>
#include <vector>
#include <unordered_map>

class GUIParser {
    public:
        // Constructor with the game name and the input vector of string
        GUIParser(const std::string& gameName, std::vector <std::string> input);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
        // produce the content of the make file in the form of a vector of strings
        std::vector <std::string> makeFile();
        // get the file name according to gamename and name
        std::string getFileName();
    private:
        // the name of the game
        std::string name;
        // the map from piece names to paths (starting from chess/img)
        std::unordered_map <std::string, std::string> paths;
};

#endif