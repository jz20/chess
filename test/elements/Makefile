CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB) -I$(COMMON)
LDLIBS		= -L$(LIB) -lelements
BUILD		= libs run
LIB			= ../../src/elements
COMMON		= ..

all:			$(BUILD)

elementstestrunner:		elementstestrunner.o boardtest.o squaretest.o
elementstestrunner.o:	elementstestrunner.h
boardtest.o:	boardtest.h
squaretest.o:	squaretest.h

clean:		
				$(RM) $(BUILD) *.o core
				cd $(LIB); make clean

libs:
				cd $(LIB); make

run:			elementstestrunner
				mv elementstestrunner run