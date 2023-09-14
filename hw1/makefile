CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: Life

clean:
	rm -f Life
	rm -rf *.dSYM

Life: main.c helpers.c life.c
	$(CC) $(CFLAGS) -o $@ $^