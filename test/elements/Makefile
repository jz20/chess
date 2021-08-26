CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB) -I$(LIBCHESS) -I$(COMMON)
LDLIBS		= -L$(LIB) -lelements -L$(LIBCHESS) -lchesselements
BUILD		= libs run
LIB			= ../../src/elements
LIBCHESS	= ../../src/elements/chess
COMMON		= ..

all:			$(BUILD)

elementstestrunner:		elementstestrunner.o boardtest.o squaretest.o chesspiecestest.o
elementstestrunner.o:	elementstestrunner.h
boardtest.o:	boardtest.h
squaretest.o:	squaretest.h
chesspiecestest.o:		chesspiecestest.h

clean:		
				$(RM) $(BUILD) *.o core
				cd $(LIBCHESS); make
				cd $(LIB); make clean

libs:
				cd $(LIBCHESS); make
				cd $(LIB); make

run:			elementstestrunner
				mv elementstestrunner run