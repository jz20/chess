CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libparser.a
LIBOBJS		= parserutils.o pieceparser.o moveparser.o
BUILD		= $(LIB)

.PHONY: 	all clean

all:	$(BUILD)

parserutils.o:	parserutils.h
pieceparser.o:	pieceparser.h
moveparser.o:	moveparser.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core