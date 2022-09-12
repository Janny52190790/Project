CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -Ofast

all: identify

identify: bf.o bv.o ht.o node.o parser.o pq.o speck.o text.o identify.o
	$(CC) -o identify  bf.o bv.o ht.o node.o parser.o pq.o speck.o text.o identify.o -lm

identify.o: identify.c
	$(CC) $(CFLAGS) -c identify.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

text.o: text.c
	$(CC) $(CFLAGS) -c text.c

clean:
	rm -f identify bf bv ht node parser pq speck text identify *.o

format:
	clang-format -i -style=file *.[c,h]

scan-build: clean
	scan-build make

