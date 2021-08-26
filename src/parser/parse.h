#ifndef PARSE_H
#define PARSE_H

#include <string>

// parse the file
void parseFile(std::string& name);

// update gitignore to not include this directory
void gitignore(std::string& directoryName);

// main
int main(int argc, char **argv);

#endif