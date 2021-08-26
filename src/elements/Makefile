CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libelements.a
LIBOBJS		= board.o square.o piece.o player.o game.o
BUILD		= $(LIB)

.PHONY: 	all clean

all:		$(BUILD)

board.o:	board.h
square.o:	square.h
piece.o:	piece.h
player.o:	player.h
game.o:		game.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core