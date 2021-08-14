#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <vector>
#include <string>

// read the content of a file and put it into a vector of strings
std::vector <std::string> readFile(const std::string& name);

// trim the input string, outputing a string with no leading or trailing blank 
// spaces
std::string trim(const std::string& str, const std::string& space = " \t\n");

#endif