CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: HookBook

clean:
	rm -f Life
	rm -rf *.dSYM

HookBook: hookbook.c skills_list.c pirate.c pirate_list.c libhookbook.c
	$(CC) $(CFLAGS) -o $@ $^