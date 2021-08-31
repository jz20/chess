#ifndef PROMOTION_PARSER_H
#define PROMOTION_PARSER_H

class PromotionParser;

typedef enum {MIRROR_PROMOTION, WHITE_PROMOTION, BLACK_PROMOTION} PromotionPlayer;

#include <vector>
#include <string>

class PromotionParser {
    public:
        // the constructor with the input
        PromotionParser(std::vector <std::string>& input, 
            std::vector <std::string>& pieces, std::vector <std::string>& trackers);
        // produce the content of the implementation cpp file in the form of a vector of strings
        std::vector <std::string> implContent();
    private:
        // the name of the pieces
        std::vector <std::string> pieces;
        // the name of the trackers
        std::vector <std::string> trackers; // not used currently, may be useful later
        // the player that the move applies to
        PromotionPlayer promotionPlayer;
        // the content of the promotion
        std::vector <std::string> instr;
        // the conditions
        std::vector <std::string> conds;
        // the or-conditions
        std::vector <std::vector <std::string>> orConds;
        // the candidates
        std::vector <std::string> candidates;
        // the targets
        std::vector <std::string> targets;
        // process a condition
        std::string processCond(const std::string& cond);
        // process an or-condition
        std::string processOrCond(std::vector <std::string>& orCond);
        // parse candidate check
        std::string parseCandidateCheck();
};

#endif