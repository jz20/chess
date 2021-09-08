CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libparser.a
LIBOBJS		= parserutils.o pieceparser.o moveparser.o trackerupdateparser.o\
				promotionparser.o gameparser.o runnerparser.o
BUILD		= $(LIB)

.PHONY: 	all clean

all:	$(BUILD) parse

parse: parse.o $(LIBOBJS)

parse.o: parse.h

parserutils.o:	parserutils.h
pieceparser.o:	pieceparser.h
moveparser.o:	moveparser.h
trackerupdateparser.o:	trackerupdateparser.h
promotionparser.o:	promotionparser.h
runnerparser.o:	runnerparser.h
gameparser.o:	gameparser.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core