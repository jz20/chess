#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <vector>
#include <string>

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
std::vector <std::string> tokenise(const std::string& str, const char& opener, 
        const char& closer, const char& delimiter);

#endif