CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: integrate

integrate: integrate.o mathlib.o functions.o
	$(CC) -o integrate integrate.o mathlib.o functions.o

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c

function.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

clean:
	rm -f integrate mathlib functions *.o

format:
	clang-format -i -style=file *.[c,h]
