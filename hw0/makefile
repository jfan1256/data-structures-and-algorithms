CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: HelloWorld HelloJack

clean:
	rm -f HelloWorld HelloJack
	rm -rf *.dSYM

HelloWorld: hello_1.c
	$(CC) $(CFLAGS) -o $@ $^

HelloJack: hello_2.c
	$(CC) $(CFLAGS) -o $@ $^
