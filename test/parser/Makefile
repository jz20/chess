CC			= g++
CPPFLAGS	= -g -Wall -I$(LIB) -I$(COMMON)
LDLIBS		= -L$(LIB) -lparser
BUILD		= libs run
LIB			= ../../src/parser
COMMON		= ..

all:			$(BUILD)

parsertestrunner:	parsertestrunner.o parserutilstest.o pieceparsertest.o moveparsertest.o\
					trackerupdateparsertest.o gameparsertest.o guiparsertest.o

parsertestrunner.o:	parsertestrunner.h
parserutilstest.o:	parserutilstest.h
pieceparsertest.o:	pieceparsertest.h
moveparsertest.o:	moveparsertest.h
trackerupdateparsertest.o:	trackerupdateparsertest.h
gameparsertest.o:	gameparsertest.h
guiparsertest.o: guiparsertest.h

clean:		
				$(RM) $(BUILD) *.o core
				cd $(LIB); make clean

libs:
				cd $(LIB); make

run:			parsertestrunner
				mv parsertestrunner run