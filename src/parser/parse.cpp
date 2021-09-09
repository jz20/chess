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

    string name = gameParser.getName();
    string fileName = gameParser.getFileName();

    string directoryName = "../elements/" + name;
    char dir[directoryName.length() + 1];
    strcpy(dir, directoryName.c_str());
    mkdir(dir, 0777);

    string header = "../elements/" + name + "/" + fileName + ".h";
    string impl = "../elements/" + name + "/" + fileName + ".cpp";
    string makefile = "../elements/" + name + "/Makefile";
    writeFile(header, gameParser.headerContent());
    writeFile(impl, gameParser.implContent());
    writeFile(makefile, gameParser.makeFile());

    for (vector <PieceParser> :: iterator it = pieceParsers->begin(); it != pieceParsers->end(); it++) {
        string pieceHeader = "../elements/" + name + "/" + it->getFileName() + ".h";
        string pieceImpl = "../elements/" + name + "/" + it->getFileName() + ".cpp";
        writeFile(pieceHeader, it->headerContent());
        writeFile(pieceImpl, it->implContent());
    }
    GUIParser *guiParser = gameParser.getReferenceToGUIParser();
    if (guiParser != NULL) {
        
        string guiDirectoryName = "../elements/" + name + "/gui";
        char dir[guiDirectoryName.length() + 1];
        strcpy(dir, guiDirectoryName.c_str());
        mkdir(dir, 0777);

        string guiHeader = "../elements/" + name + "/gui/" + guiParser->getFileName() + ".h";
        string guiImpl = "../elements/" + name + "/gui/" + guiParser->getFileName() + ".cpp";
        string guiMakefile = "../elements/" + name + "/gui/Makefile";
        writeFile(guiHeader, guiParser->headerContent());
        writeFile(guiImpl, guiParser->implContent());
        writeFile(guiMakefile, guiParser->makeFile());
    }

    string ignoreDir = name + "/";
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