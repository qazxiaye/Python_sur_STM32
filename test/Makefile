SHEDSKIN_LIBDIR=/usr/local/lib/python2.7/dist-packages/shedskin/lib
CC=g++
CCFLAGS=-O2 -march=native -Wno-deprecated $(CPPFLAGS) -I. -I${SHEDSKIN_LIBDIR}
LFLAGS=-lgc -lpcre $(LDFLAGS)

CPPFILES=/home/xavier/ricm/mul_projet/py2stm/test/10.cpp \
	${SHEDSKIN_LIBDIR}/re.cpp \
	${SHEDSKIN_LIBDIR}/builtin.cpp

HPPFILES=/home/xavier/ricm/mul_projet/py2stm/test/10.hpp \
	${SHEDSKIN_LIBDIR}/re.hpp \
	${SHEDSKIN_LIBDIR}/builtin.hpp

all:	10

10:	$(CPPFILES) $(HPPFILES)
	$(CC)  $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o 10

10_prof:	$(CPPFILES) $(HPPFILES)
	$(CC) -pg -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o 10_prof

10_debug:	$(CPPFILES) $(HPPFILES)
	$(CC) -g -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o 10_debug

clean:
	rm -f 10 10_prof 10_debug

.PHONY: all clean

