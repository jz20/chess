#include "parserutilstest.h"

#include "parserutils.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>

using namespace std;

// in each unit test true signals success

// test the readFile function, the content of sample.txt should be the following
/*


// this is a comment
#PIECE (pig, p) {
    (1, 0)
}

*/
bool readFileTest() {
    string name = "./sample.txt";
    size_t expected = 3;
    vector <string> lines = readFile(name);
    if (lines.size() != expected) {
        return false;
    }
    return lines[0] == "#PIECE(pig,p){"
            && lines[1] == "(1,0)"
            && lines[2] == "}";
}

// test the trim function
bool trimTest() {
    string s1 = "   pig live in hole";
    string s2 = "piggy glide     ";
    string s3 = "      pig ";
    return (trim(s1) == "pig live in hole") && (trim(s2) == "piggy glide") && (trim(s3) == "pig");
}

// test the tokenise function
bool tokeniseTest() {
    string sample = "#PIECE(queen,q){";
    vector <string> tokens = tokenise(sample, '(', ')', ',');
    size_t expected = 2;
    if (tokens.size() != expected) {
        return false;
    }
    return tokens[0] == "queen"
            && tokens[1] == "q";
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runParserUtilsTests() {
    cout << "Parser Utils Test: \n";
    bool result = true;
    TEST(tokeniseTest, "tokenise");
    TEST(trimTest, "trim");
    TEST(readFileTest, "file reading");
    return result;
}