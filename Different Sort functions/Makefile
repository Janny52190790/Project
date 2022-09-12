CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting

sorting : batcher.o insert.o heap.o quick.o stats.o sorting.o 
	$(CC) -o sorting batcher.o insert.o heap.o quick.o stats.o sorting.o -lm

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

clean:
	rm -f batcher insert heap quick stats sorting *.o

format:
	clang-format -i -style=file *.[c,h]
