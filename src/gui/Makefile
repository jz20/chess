CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB)
LDLIBS		= -L$(LIB) -lelements $(WXLINK)
BUILD		= lib run
LIB			= ../elements $(WXPATH)
WXLINK		= `wx-config --cxxflags --libs std`
WXPATH		= `wx-config --cxxflags std`

all:		$(BUILD)

chessgamerunner:		chessgamerunner.o chesssquarepanel.o chesspiecebitmap.o

chessgamerunner.o:		chessgamerunner.h
chesspiecebitmap.o:		chesspiecebitmap.h

clean:		
			$(RM) $(BUILD) *.o core
#			cd $(LIB); make clean

lib:		
			cd $(LIB); make

run:		chessgamerunner
			mv chessgamerunner run