CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: HookBook

clean:
	rm -f Life
	rm -rf *.dSYM

HookBook: hookbook.c pirate.c pirate_list.c libhookbook.c
	$(CC) $(CFLAGS) -o $@ $^