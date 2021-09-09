CC			= g++
CPPFLAGS	= -g -Wall -I$(ELEM) -I$(CHESS) $(WXPATH)
LDLIBS		= -L$(ELEM) -lelements -L$(CHESS) -lchesselements $(WXLINK)
LIB			= libgui.a
LIBOBJS		= gamerunner.o piecebitmap.o gameframe.o
BUILD		= $(LIB) elem run
ELEM		= ../elements
CHESS		= ../elements/chess
WXLINK		= `wx-config --cxxflags --libs std`
WXPATH		= `wx-config --cxxflags std`

all:		$(BUILD)

chessgamerunner:	gamerunner.o piecebitmap.o gameframe.o chessgamerunner.o

chessgamerunner.o:	chessgamerunner.h
gameframe.o:	gameframe.h
gamerunner.o:	gamerunner.h
piecebitmap.o:	piecebitmap.h

clean:		
			$(RM) $(BUILD) *.o core
#			cd $(LIB); make clean

elem:		
			cd $(ELEM); make

$(LIB):		$(LIBOBJS)
		ar rcs $(LIB) $(LIBOBJS)

run:		chessgamerunner
			mv chessgamerunner run