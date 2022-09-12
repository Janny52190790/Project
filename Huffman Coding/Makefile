CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g

all: encode decode

encode: encode.o node.o pq.o code.o io.o huffman.o stack.o
	$(CC) -o encode encode.o node.o pq.o code.o io.o huffman.o stack.o

decode: decode.o node.o pq.o code.o io.o huffman.o stack.o
	$(CC) -o decode decode.o node.o pq.o code.o io.o huffman.o stack.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f encode decode node pq code io huffman stack *.o

format:
	clang-format -i -style=file *.[c,h]
