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
```

## the command-line options your program accepts

• -a : Employs all sorting algorithms.\
• -h: Enables Heap Sort\
• -i: Enables Insertion Sort\
• -b : Enables Batcher Sort.\
• -q : Enables Quicksort\
• -r seed : Set the random seed to seed. The default seed should be 13371453.\
• -n size : Set the array size to size. The default size should be 100.\
• -p elements : Print out elements number of elements from the array. The default number of\
elements to print out should be 100. If the size of the array is less than the specified number of\
elements to print, print out the entire array and nothing more.\
• -H: Prints out program usage.\
