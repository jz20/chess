#include "parserutils.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// read the content of a file and put it into a vector of strings
// removes all spaces
vector <string> readFile(const string& name) {
    vector <string> lines;
    ifstream in(name);
    string str = "";
    while (getline(in, str)) {
        str = trim(str);
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        if (str.size() > 0 && !regex_match(str, regex("^\\/\\/(.*)"))) {
            lines.push_back(str);
        }
    }
    in.close();
    return lines;
}

// write the content of a vector of strings to a file
void writeFile(const string& name, const vector <string>& lines) {
    ofstream out(name);
    for (const string& line : lines) {
        out << line << "\n";
    }
    out.close();
}

// trim the input string, outputing a string with no leading or trailing blank 
// spaces
string trim(const string& str, const string& space) { // space = " \t\n"
    const size_t start = str.find_first_not_of(space);
    const size_t end = str.find_last_not_of(space);
    // for some reason str.substr(start, end - 1) does not work
    return ((start == string::npos) || (end == string::npos)) ? "" : str.substr(start).substr(0, end + 1 - start);
}

// tokenise the text between the first occurrence of opener and the first
// occurrence of closer, seperated by the delimiter
vector <string> tokenise(const string& str, const char& opener, 
        const char& closer, const char& delimiter) {
    vector <string> tokens;
    const size_t start = str.find_first_of(string(1, opener));
    const size_t end = str.find_first_of(string(1, closer));
    if (start != string::npos && end != string::npos && end - start > 1) {
        string all = str.substr(start + 1).substr(0, end - 1 - start);
        stringstream sstream(all);
        string token;
        while (getline(sstream, token, delimiter)) {
            tokens.push_back(token);
        }
    }
    return tokens;
}