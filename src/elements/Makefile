CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libelements.a
LIBOBJS		= board.o square.o
BUILD		= $(LIB)

all:		$(BUILD)

board.o:	board.h
square.o:	square.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core