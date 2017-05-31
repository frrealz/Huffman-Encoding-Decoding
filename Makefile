CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g

.PHONY: all
all: encode

		
encode		:	encode.o
		$(CC) $(CFLAGS) -o encode encode.o
encode.o	:	encode.c
		$(CC) $(CFLAGS) -c encode.c

clean	:
		rm encode.o encode