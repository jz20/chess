#include "parserutils.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// read the content of a file and put it into a vector of strings
vector <string> readFile(const std::string& name) {
    vector <string> lines;
    ifstream in(name);
    string str = "";
    while (getline(in, str)) {
        if (str.size() > 0) {
            lines.push_back(str);
        }
    }
    return lines;
}

// trim the input string, outputing a string with no leading or trailing blank 
// spaces
string trim(const string& str, const string& space) {
    const size_t start = str.find_first_not_of(space);
    const size_t end = str.find_last_not_of(space);
    return ((start == string::npos) || (end == string::npos)) ? "" : str.substr(start, end + 1);
}