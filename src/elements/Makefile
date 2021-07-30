CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libelements.a
CHESSLIB	= cpbishop.o cprook.o cpqueen.o cpknight.o cpking.o cppawn.o chessgame.o
LIBOBJS		= board.o square.o piece.o player.o game.o $(CHESSLIB)
BUILD		= $(LIB)

all:		$(BUILD)

board.o:	board.h
square.o:	square.h
piece.o:	piece.h
player.o:	player.h
game.o:		game.h

# cp - chess pieces
cpbishop.o:		cpbishop.h
cprook.o:		cprook.h
cpqueen.o:		cpqueen.h
cpknight.o:		cpknight.h
cpking.o:		cpking.h
cppawn.o:		cppawn.h
# chess game
chessgame.o:	chessgame.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core