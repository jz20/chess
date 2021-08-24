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

// return the number of lines, after which the current block {} finishes
// start denotes the index of the start of the block
int blockSize(vector <string>& content, size_t start) {
    if (content.size() <= start) {
        return 0;
    }
    int count = 0;
    int bracket = 0;
    string current = "";
    for (vector <string> :: iterator it = content.begin() + start; it != content.end(); it++) {
        current = *it;
        if (current.find('{') != string::npos) {
            bracket++;
        } else if (current.find('}') != string::npos) {
            bracket--;
        }
        count++;
        if (bracket == 0) {
            return count;
        }
    }
    return 0;
}

// find the target find in str and replace it with replace
string findAndReplace(const string& str, const string& find, const string& replace) {
    string result = str;
    size_t index = 0;
    while (true) {
        index = result.find(find, index);
        if (index == string::npos) {
            break;
        }
        result.erase(index, find.length());
        result.insert(index, replace);
    }
    return result;
}