#include "trackerupdateparsertest.h"

#include "trackerupdateparser.h" // from corresponding source
#include "testutil.h" // from ..
#include <iostream>
#include <string>
#include <vector>
#include "parserutils.h"

using namespace std;

// test the cpp implementation is created correctly
bool trackerUpdateImplTest() {
    vector <string> content = readFile("test_examples/trackerupdateexample.txt");
    vector <string> baz;
    TrackerUpdateParser p(content);
    writeFile("test_examples/trackerupdateimpl.txt", p.implContent());
    cout << "\tfor details check test_examples/trackerupdateimpl.txt: ";
    return true;
}

// run the tests and output the results
bool runTrackerUpdateParserTests() {
    cout << "Tracker Update Parser Test: \n";
    bool result = true;
    TEST(trackerUpdateImplTest, "implementation file")
    return result;
}