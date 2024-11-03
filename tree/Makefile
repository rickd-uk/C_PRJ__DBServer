CC= gcc
CFLAGS=-Wall -O2 -std=c2x
LDFLAGS=

.SUFFIXES: .c .o

all: tree


tree: tree.o
	$(CC) ${CFLAGS} $^ -o $@ ${LDFLAGS}

%.o: %.c
	$(CC) ${CFLAGS} -c $^

clean:
	rm -rf *.o tree

.PHONY:
	all clean

-include *.d
