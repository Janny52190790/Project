#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTION "ahbiqHr:n:p:"
#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "stats.h"

#define ASA 1
#define HS  2
#define BS  3
#define IS  4
#define QS  5

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Test different sorting functions using pseudorandom elements.\n"
        "\n"
        "USAGE\n"
        "   %s [ahbiqHr:n:p:] [-r seed] [-n size] [-p elements]\n"
        "\n"
        "OPENTIONS\n"
        "   -a  Employs all sorting algorithms.\n"
        "   -h  Enables Heap Sort.\n"
        "   -b  Enables Batcher Sort.\n"
        "   -i  Enables Insertion Sort.\n"
        "   -q  Enables Quicksort.\n"
        "   -r  seed    Set the random seed to seed. The default seed should be 13371453.\n"
        "   -n  size    Set the array size to size. The default size should be 100.\n"
        "   -p  elements    Print out elements number of elements from the array. The default number of\
                                elements to print out should be 100.\n"
        "   -H  Prints out program usage. See reference program for example of what to print.\n",
        exec);
}

int main(int argc, char **argv) {
    int elements = 100;
    int size = 100;
    uint32_t seed = 13371453;
    srandom(seed);
    Set arguments = empty_set();
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTION)) != -1) {
        switch (opt) {
        // use set
        case 'a': arguments = insert_set(ASA, arguments); break;
        case 'h': arguments = insert_set(HS, arguments); break;
        case 'b': arguments = insert_set(BS, arguments); break;
        case 'i': arguments = insert_set(IS, arguments); break;
        case 'q': arguments = insert_set(QS, arguments); break;
        case 'r':
            seed = (uint32_t) strtoul(optarg, NULL, 10);
            break;
            srandom(seed);
        case 'n': size = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'p': elements = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'H': usage(argv[0]); return EXIT_FAILURE;
        }
    }

    if (size < elements) {
        elements = size;
    }

    uint32_t *A;
    A = (uint32_t *) malloc(size * sizeof(uint32_t));
    for (int i = 0; i < size; i++) {
        A[i] = random() & (int) (pow(2, 30) - 1);
    }
    // create a random list
    uint32_t n = size;
    Stats *sortingstats = malloc(sizeof(Stats));
    if (member_set(2, arguments)) {
        reset(sortingstats);
        heap_sort(sortingstats, A, n);
        printf("Heap Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A);
    }

    //reset()
    else if (member_set(3, arguments)) {
        reset(sortingstats);
        batcher_sort(sortingstats, A, n);
        printf("Batcher Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A);
    }

    else if (member_set(4, arguments)) {
        reset(sortingstats);
        insertion_sort(sortingstats, A, n);
        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A);
    }

    else if (member_set(5, arguments)) {
        reset(sortingstats);
        quick_sort(sortingstats, A, n);
        printf("Quick Sort, %d elements, %li moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A);
    }

    else if (member_set(1, arguments)) {
        reset(sortingstats);
        insertion_sort(sortingstats, A, n);
        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A);

        reset(sortingstats);
        srandom(seed);
        //reset A list
        uint32_t *A1;
        A1 = (uint32_t *) malloc(size * sizeof(uint32_t));
        for (int i = 0; i < size; i++) {
            A1[i] = random() & (int) (pow(2, 30) - 1);
        }
        uint32_t n1 = size;

        batcher_sort(sortingstats, A1, n1);
        printf("Batcher Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A1[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A1);

        reset(sortingstats);
        srandom(seed);
        //reset A
        uint32_t *A2;
        A2 = (uint32_t *) malloc(size * sizeof(uint32_t));
        for (int i = 0; i < size; i++) {
            A2[i] = random() & (int) (pow(2, 30) - 1);
        }
        uint32_t n2 = size;

        heap_sort(sortingstats, A2, n2);
        printf("Heap Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A2[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A2);

        reset(sortingstats);
        srandom(seed);
        // reset A
        uint32_t *A3;
        A3 = (uint32_t *) malloc(size * sizeof(uint32_t));
        for (int i = 0; i < size; i++) {
            A3[i] = random() & (int) (pow(2, 30) - 1);
        }
        uint32_t n3 = size;

        quick_sort(sortingstats, A3, n3);
        printf("Quick Sort, %d elements, %lu moves, %lu compares\n", n, sortingstats->moves,
            sortingstats->compares);
        for (int j = 0; j < elements; j++) {
            printf("%13" PRIu32, A3[j]);
            if ((j + 1) % 5 == 0) {
                printf("\n");
            }
        }
        free(A3);
    }
    free(sortingstats);
    return 0;
}
