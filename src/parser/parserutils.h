#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <vector>
#include <string>

// requires vector <string> content and int indent to be defined
#define W(line) content.push_back(string(indent, '\t') + line);

// requires vector <string> content and int indent to be defined
#define W_(line) \
    content.push_back(string(indent, '\t') + line); \
    indent++;

// requires vector <string> content and int indent to be defined
#define _W(line) \
    indent--; \
    content.push_back(string(indent, '\t') + line);

// requires vector <string> content and int indent to be defined
#define _W_(line) \
    indent--; \
    content.push_back(string(indent, '\t') + line); \
    indent++;

// requires vector <string> content and int indent to be defined
#define _WE indent--; 

// requires vector <string> content to be defined
#define WN content.push_back("");

#define POP_FRONT(name) \
    if (!name.empty()) { \
        name.erase(name.begin()); \
    }

// read the content of a file and put it into a vector of strings
// removes all spaces
std::vector <std::string> readFile(const std::string& name);

// write the content of a vector of strings to a file
void writeFile(const std::string& name, const std::vector <std::string>& lines);

// trim the input string, outputing a string with no leading or trailing blank 
// spaces
std::string trim(const std::string& str, const std::string& space = " \t\n");

// tokenise the text between the first occurrence of opener and the first
// occurrence of closer, seperated by the delimiter
std::vector <std::string> tokenise(const std::string& str, const char& opener = '(', 
        const char& closer = ')', const char& delimiter = ',');

// return the number of lines, after which the current block {} finishes
// start denotes the index of the start of the block
int blockSize(std::vector <std::string>& content, size_t start);

// find the target find in str and replace it with replace
std::string findAndReplace(const std::string& str, const std::string& find, const std::string& replace);

// increase the indent by the amount in an entire vector of strings
void increaseIndent(std::vector <std::string>& input, int amount);

// replace some keywords with their meaning in a condition
std::string replaceKeywords(const std::string& cond);

#endif