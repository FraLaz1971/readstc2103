CC=gcc
LD=gcc
.PHONY: all clean
CFLAGS=-c
LDFLAGS=-L$(CFITSIO_HOME)
LIBS=-lcfitsio
OEXT=.o
EEXT=

readstc2103$(OEXT): readstc2103.c
	$(CC) $(CFLAGS) $<

readstc2103$(EEXT): readstc2103$(OEXT)
	$(CC)  $< -o $@ $(LDFLAGS) $(LIBS)

clean: rm *.o readstc2103
