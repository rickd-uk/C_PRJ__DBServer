CC=cc
flags=-O2 -Wall -std=c2x
ldflags=

.PHONY: all clean

all: cache22

cache22: cache22.o
	$(CC) $(flags) $^ -o $@ $(ldflags)


%.o: %.c
	$(CC) $(flags) -c $< -o $@ 

clean:
	rm -f *.o cache22

