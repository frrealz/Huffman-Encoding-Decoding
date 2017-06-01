CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g

.PHONY: all
all: encode

		
encode		:	encode.o queue.o
		$(CC) $(CFLAGS) queue.o -o encode encode.o
encode.o	:	encode.c
		$(CC) $(CFLAGS) -c encode.c
		
queue.o	:	queue.c
		$(CC) $(CFLAGS) -c 	queue.c			
# huffman.o	:	huffman.c
		# $(CC) $(CFLAGS) -c 	huffman.c				

clean	:
		rm encode.o encode