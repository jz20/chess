#include "guiparser.h"

#include "parserutils.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Constructor with the game name and the input vector of string
GUIParser::GUIParser(const string& gameName, vector <string> input) {
    this->name = gameName;
    try {
        for (vector <string> :: iterator it = input.begin() + 1; it != input.end() - 1; it++) {
            string name = "";
            vector <string> tokens = tokenise(*it);
            if (tokens[0] == "#WHITE") {
                name += "white_";
            } else {
                name += "black_";
            }
            name += tokens[1];
            paths[name] = tokens[2];
        }
    } catch (exception& e) {
        cout << "incorrect paths for pieces" << "\n";
    }
}

// produce the content of the header file in the form of a vector of strings
vector <string> GUIParser::headerContent() {
    string def = name;
    def += "_RUNNER_H";
    transform(def.begin(), def.end(), def.begin(), ::toupper);
    
    string className = name + "Runner";
    className[0] = toupper(className[0]);

    vector <string> content;
    int indent = 0;

    W("#ifndef " + def)
    W("#define " + def)
    WN
    W("class " + className + ";")
    WN
    W("#include <wx/wxprec.h>")
    W("#ifndef WX_PRECOMP")
    W("#include <wx/wx.h>")
    W("#endif")
    W("#include <vector>")
    W("#include <unordered_map>")
    W("#include \"game.h\"")
    W("#include \"gamerunner.h\"")
    W("#include \"gameframe.h\"")
    W("#include \"piecebitmap.h\"")
    WN
    W_("class " + className + ": public GameRunner {")
    W_("public:")
    W("virtual bool OnInit();")
    _WE
    _W("};")
    WN
    W("#endif")

    return content;
}

// produce the content of the implementation cpp file in the form of a vector of strings
vector <string> GUIParser::implContent() {
    vector <string> content;
    int indent = 0;

    string className = name + "Runner";
    className[0] = toupper(className[0]);

    string gameClass = name + "Game";
    gameClass[0] = toupper(gameClass[0]);

    W("#include \"" + getFileName() + ".h\"")
    WN
    W("#include <wx/wxprec.h>")
    W("#ifndef WX_PRECOMP")
    W("#include <wx/wx.h>")
    W("#endif")
    W("#include <vector>")
    W("#include <unordered_map>")
    W("#include \"game.h\"")
    W("#include \"gamerunner.h\"")
    W("#include \"gameframe.h\"")
    W("#include \"piecebitmap.h\"")
    W("#include \"" + name + "game.h\"")
    WN
    W("using namespace std;")
    WN
    W_("bool " + className + "::OnInit() {")
        W("wxInitAllImageHandlers();")
        W("game = new " + gameClass + "();")
        W("unordered_map <string, string> paths;")
        for (auto path:paths) {
            W("paths[\"" + path.first + "\"] = \"" + path.second + "\";")
        }
        W("frame = new GameFrame(\"" + gameClass + "\", game, this, paths);")
        W("game->setUp();")
        W("frame->updatePieces();")
        W("frame->Show(true);")
        W("return true;")
    _W("}")
    WN
    W("wxIMPLEMENT_APP(" + className + ");")

    return content;
}

// produce the content of the make file in the form of a vector of strings
vector <string> GUIParser::makeFile() {
    vector <string> content;
    int indent = 0;
    W("CC\t= g++")
    W("CPPFLAGS\t= -g -Wall -I$(COMMON)")
    W("LDLIBS\t= -L$(COMMON) -lelements")
    W("COMMON\t= ..")
    W("BUILD\t= common run" + name)
    WN
    W(".PHONY:\tall clean")
    WN
    W("all:\t$(BUILD)")
    WN
    string linking = "run" + name + ":\t run" + name + ".o";
    linking += " " + name + "game.o";
    W(linking)
    W("run" + name + ".o:\trun" + name + ".h")
    WN
    W(name + "game.o:\t" + name + "game.h")
    WN
    WN
    W("common:")
    W("\t\tcd $(COMMON); make")
    WN
    W("clean:")
    W("\t\t$(RM) $(BUILD) *.o core")
    W("\t\tcd $(COMMON); make clean")
    return content;
}

// get the file name according to gamename and name
string GUIParser::getFileName() {
    return name + "runner";
}