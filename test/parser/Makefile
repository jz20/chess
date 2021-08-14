CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB) -I$(COMMON)
LDLIBS		= -L$(LIB) -lparser
BUILD		= libs run
LIB			= ../../src/parser
COMMON		= ..

all:			$(BUILD)

parsertestrunner:	parsertestrunner.o parserutilstest.o

parsertestrunner.o:	parsertestrunner.h
parserutilstest.o:	parserutilstest.h

clean:		
				$(RM) $(BUILD) *.o core
				cd $(LIB); make clean

libs:
				cd $(LIB); make

run:			parsertestrunner
				mv parsertestrunner run