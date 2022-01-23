# Assignment 1 - Getting Acquainted with UNIX and C
This assignment mainly ask as to make four soring functions: batcher.c, insert.c, heap.c, quick.c which are four different ways to sort a list. We also need to calculate the times of moves and compares for each sorting function. We will also cresate a c file called sorting.c which is a main function that use getopt() to call the four sorting functions and print out the statements . We should also create Makefile and DESIGN.pdf WRITEUP.pdf.

## Automate compilation by using Makefile
```
$ make
```

## Cleaning
```
$ make clean
```

## Running

```
$ ./sorting  -<sort> -r <seed> -n <size> -p <elements>
