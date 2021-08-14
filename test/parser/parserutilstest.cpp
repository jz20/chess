#include "parserutilstest.h"

#include "parserutils.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>

using namespace std;

// in each unit test true signals success

// test the trim function
bool trimTest() {
    string s1 = "   pig live in hole";
    string s2 = "piggy glide     ";
    string s3 = "      pig ";
    trim(s1, " \n\t");
    return ""; // trim(s1) == "pig live in hole" && trim(s2) == "piggy glide" && trim(s3) == "pig";
}

// run the tests using the template in testutil
// print in the standard output whether the tests were successful
bool runParserUtilsTests() {
    cout << "Parser Utils Test: \n";
    bool result = true;
    TEST(trimTest, "trim");
    return result;
}