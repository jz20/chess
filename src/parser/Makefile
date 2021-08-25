CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libparser.a
LIBOBJS		= parserutils.o pieceparser.o moveparser.o trackerupdateparser.o promotionparser.o gameparser.o
BUILD		= $(LIB)

.PHONY: 	all clean

all:	$(BUILD)

parserutils.o:	parserutils.h
pieceparser.o:	pieceparser.h
moveparser.o:	moveparser.h
trackerupdateparser.o:	trackerupdateparser.h
promotionparser.o:	promotionparser.h
gameparser.o:	gameparser.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core