CC			= g++
CPPFLAGS	= -g -Wall -I$(COMMON)
LDLIBS		= -L$(COMMON) -lelements
COMMON		= ..
LIB			= libchesselements.a
LIBOBJS		= cpbishop.o cprook.o cpqueen.o cpknight.o cpking.o cppawn.o chessgame.o
BUILD		= common $(LIB) runchess

.PHONY: 	all clean

all:		$(BUILD)

# game runner
runchess:	runchess.o $(LIBOBJS)
runchess.o:	runchess.h

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

common:
				cd $(COMMON); make

clean:
			$(RM) $(BUILD) *.o core
			cd $(COMMON); make clean