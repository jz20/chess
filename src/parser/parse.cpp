#include "parse.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include "parserutils.h"
#include "gameparser.h"
#include "pieceparser.h"

using namespace std;

// parse the file
void parseFile(string& file) {
    vector <string> content = readFile(file);
    GameParser gameParser = GameParser(content);
    vector <PieceParser> *pieceParsers = gameParser.getReferenceToPieceParsers();

    string directoryName = "../elements/" + gameParser.getName();
    char dir[directoryName.length() + 1];
    strcpy(dir, directoryName.c_str());
    mkdir(dir, 0777);

    string header = "../elements/" + gameParser.getName() + "/" + gameParser.getFileName() + ".h";
    string impl = "../elements/" + gameParser.getName() + "/" + gameParser.getFileName() + ".cpp";
    writeFile(header, gameParser.headerContent());
    writeFile(impl, gameParser.implContent());

    for (vector <PieceParser> :: iterator it = pieceParsers->begin(); it != pieceParsers->end(); it++) {
        string pieceHeader = "../elements/" + gameParser.getName() + "/" + it->getFileName() + ".h";
        string pieceImpl = "../elements/" + gameParser.getName() + "/" + it->getFileName() + ".cpp";
        writeFile(pieceHeader, it->headerContent());
        writeFile(pieceImpl, it->headerContent());
    }

    string ignoreDir = gameParser.getName() + "/";
    gitignore(ignoreDir);
}

// update gitignore to not include this directory
void gitignore(std::string& directoryName) {
    ofstream out;
    out.open("../elements/.gitignore", ios_base::app);
    out << directoryName << "\n";
}

// main
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "please enter the file to be parsed\n";
        throw argc;
    }
    string file = argv[1];
    parseFile(file);
}