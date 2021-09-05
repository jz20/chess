#ifndef RUNNER_PARSER_H
#define RUNNER_PARSER_H

class RunnerParser;

#include <string>
#include <vector>
#include <unordered_map>

class RunnerParser {
    public:
        // Constructor with the game name and the input vector of string
        RunnerParser(const std::string& gameName, std::vector <std::string> input);
        // produce the content of the header file in the form of a vector of strings
        std::vector <std::string> headerContent();
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
        // get the file name according to gamename and name
        std::string getFileName();
    private:
        // the name of the game
        std::string name;
        // the map from piece names to paths (starting from chess/img)
        std::unordered_map <std::string, std::string> paths;
};

#endif