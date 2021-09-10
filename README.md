# chess



This is my programming project.  
Step 1: program the functionalities of a chess game  
Step 2: implement the GUI for the chess game using wxWidgets: [Guide for Ubuntu](https://www.binarytides.com/install-wxwidgets-ubuntu/), [Main Page](https://www.wxwidgets.org/)  
Step 3: provide ways to customly create chess-like board games <- CURRENT  

Note: At its current stage, the program does not have a main product file. 

To play chess using the GUI (requires wxWidgets):  
```cd src/gui; make; ./run```

To play chess using the CLI:  
```cd src/elements/chess; make; ./runchess```

To parse a custom game:  
cd src/parser; make; ./parse \[path to the gamefile to be parsed\]  
Note: It's recommended to put the gamefile in the directory gamefiles

After parsing a custom game:
To play the game using the GUI, open src/elements/\[gamename\]/gui, then  
```make; ./run```

To test the elements and chess:  
```cd test/elements; make; ./run```

To test the parser:  
```cd test/elements; make; ./run```  
Note: For some test, the result will always be success because the success cannot be easily verified automatically. In this case, there will be instruction to check the output files.

![Progress gif](https://github.com/jz20/chess/blob/main/progress.gif)
