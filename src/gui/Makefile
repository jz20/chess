CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB) -I$(LIBCHESS) $(WXPATH)
LDLIBS		= -L$(LIB) -lelements -L$(LIBCHESS) -lchesselements $(WXLINK)
BUILD		= lib run
LIB			= ../elements
LIBCHESS	= ../elements/chess
WXLINK		= `wx-config --cxxflags --libs std`
WXPATH		= `wx-config --cxxflags std`

all:		$(BUILD)

chessgamerunner:		chessgamerunner.o chesspiecebitmap.o

chessgamerunner.o:		chessgamerunner.h
chesspiecebitmap.o:		chesspiecebitmap.h

clean:		
			$(RM) $(BUILD) *.o core
#			cd $(LIB); make clean
#			cd $(CHESSLIB); make clean

lib:		
			cd $(LIB); make
			cd $(CHESSLIB); make

run:		chessgamerunner
			mv chessgamerunner run