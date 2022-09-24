.PHONY: clean all

SOURCES	:= $(wildcard *.c)
PROGS	:= $(SOURCES:%.c=%)

CFLAGS	:= -O3 -Wall

all: $(PROGS)

clean:
	rm -fr $(PROGS) *.dSYM
