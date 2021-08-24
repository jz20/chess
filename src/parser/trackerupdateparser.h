#ifndef TRACKER_UPDATE_PARSER_H
#define TRACKER_UPDATE_PARSER_H

class TrackerUpdateParser;

#include <vector>
#include <string>

class TrackerUpdateParser {
    public:
        // constructor with the input vector of strings
        TrackerUpdateParser(std::vector <std::string>& input);
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
    private:
        // the instructions
        std::vector <std::string> instr;
        // the conditions
        std::vector <std::string> conds;
        // the or conditions
        std::vector <std::vector <std::string>> orConds;
        // process a condition
        std::string processCond(const std::string& cond);
        // process an or-condition
        std::string processOrCond(std::vector <std::string>& orCond);
};

#endif