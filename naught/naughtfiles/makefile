NCC = ../comp
CPP = cpp
CC = gcc
INCDIRS = -I ../nstdlib
CFLAGS = -c -g -Wall -std=c99
LDFLAGS = -L ../nstdlib -lnaught

EXES = example strings lvalue swap tiny 333test1

.PRECIOUS: %.c

all: $(EXES)

example: example.o fact.o initLabel.o ../comp
	 $(CC) example.o fact.o initLabel.o -o example $(LDFLAGS)
	 ./example

%.c : %.n ../comp
	$(CPP) $(INCDIRS) $< | $(NCC) -d -o $@ -
	cat $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCDIRS) $<

clean:
	rm -f *~ *.o *.c $(EXES)