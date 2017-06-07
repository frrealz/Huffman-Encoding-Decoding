CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g

.PHONY: all 
all: encode decode

encode: encode.o queue.o huffman.o
	$(CC) $(CFLAGS) encode.o queue.o huffman.o $(CFLAGS) -o encode

encode.o: encode.c code.h
	$(CC) $(CFLAGS) -c encode.c	

decode: decode.o stack.o huffman.o
	$(CC) $(CFLAGS) decode.o stack.o huffman.o $(CFLAGS) -o decode

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c


.PHONY: clean
clean:
	rm decode.o stack.o huffman.o decode
	rm encode.o queue.o huffman.o encode
