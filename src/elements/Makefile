CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libelements.a
CPLIB		= cpbishop.o cprook.o
LIBOBJS		= board.o square.o piece.o $(CPLIB)
BUILD		= $(LIB)

all:		$(BUILD)

board.o:	board.h
square.o:	square.h
piece.o:	piece.h

# cp - chess pieces
cpbishop.o:	cpbishop.h
cprook.o:	cprook.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core