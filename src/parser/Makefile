CC			= g++
CPPFLAGS	= -g -Wall
LIB			= libparser.a
LIBOBJS		= parserutils.o
BUILD		= $(LIB)

.PHONY: 	all clean

all:	$(BUILD)

parserutils.o:	parserutils.h

$(LIB):		$(LIBOBJS)
			ar rcs $(LIB) $(LIBOBJS)

clean:
			$(RM) $(BUILD) *.o core