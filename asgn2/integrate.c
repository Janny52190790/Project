#include "functions.h"
#include "mathlib.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTION "n:p:q:abcdefghijH"

// define program help and usage
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Prints the numerical integration of a function over a specified interval using the "
        "composite Simpson’s rule.\n"
        "\n"
        "USAGE\n"
        "   %s [abcdefghijHn:p:q:] [-n partition] [-p low] [-q high]\n"
        "\n"
        "OPTIONS\n"
        "   -h         display program help and usage.\n"
        "   -n partitions   Sets the upper limit of partitions to use in the composite Simpson’s "
        "rule to partitions. \n"
        "   -p low   Sets the low end of the interval to integrate over to low.\n"
        "   -q high   Sets the high end of the interval to integrate over to high. This should not "
        "have a defaultvalue and must be specified each time the program is run.\n"
        "   -a   Sets the function to integrate to sqrt(1 - x^4)\n."
        "   -b   Sets the function to integrate to 1/log(x).\n"
        "   -c   Sets the function to integrate to e^((−x)^2).\n"
        "   -d   Sets the function to integrate to sin(x^2).\n"
        "   -e   Sets the function to integrate to cos(x^2).\n"
        "   -f   Sets the function to integrate to log(log(x)).\n"
        "   -g   Sets the function to integrate to sin(x)/x.\n"
        "   -h   Sets the function to integrate to (e^(−x))/x.\n"
        "   -i   Sets the function to integrate to e^(e^x).\n"
        "   -j   Sets the function to integrate to sqrt((sin(x))^2 + (cos(x))^2).\n"
        "   -H   Displays the program’s usage and synopsis.\n",
        exec);
}
//define each cases
int main(int argc, char **argv) {
    int option;
    double low;
    double high;
    uint32_t partition = 100;
    int a_integrate = 0;
    int b_integrate = 0;
    int c_integrate = 0;
    int d_integrate = 0;
    int e_integrate = 0;
    int f_integrate = 0;
    int g_integrate = 0;
    int h_integrate = 0;
    int i_integrate = 0;
    int j_integrate = 0;
    while ((option = getopt(argc, argv, OPTION)) != -1) {
        switch (option) {
        case 'p': low = (double) strtod(optarg, (char **) NULL); break;
        case 'q': high = (double) strtod(optarg, (char **) NULL); break;
        case 'n': partition = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'a': a_integrate = 1; break;
        case 'b': b_integrate = 1; break;
        case 'c': c_integrate = 1; break;
        case 'd': d_integrate = 1; break;
        case 'e': e_integrate = 1; break;
        case 'f': f_integrate = 1; break;
        case 'g': g_integrate = 1; break;
        case 'h': h_integrate = 1; break;
        case 'i': i_integrate = 1; break;
        case 'j': j_integrate = 1; break;
        case 'H': usage(argv[0]); return EXIT_FAILURE;
        }
    }
    //print the first line output like: <function>,<low>,<high>,<partitions>
    if (a_integrate) {
        printf("sqrt(1 - x^4), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (b_integrate) {
        printf("1/log(x), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (c_integrate) {
        printf("e^((−x)^2), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (d_integrate) {
        printf("sin(x^2), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (e_integrate) {
        printf("cos(x^2), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (f_integrate) {
        printf("log(log(x)), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (g_integrate) {
        printf("sin(x)/x, %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (h_integrate) {
        printf("(e^(−x))/x, %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (i_integrate) {
        printf("e^(e^x), %0.6lf,%0.6lf,%d\n", low, high, partition);
    } else if (j_integrate) {
        printf("sqrt((sin(x))^2 + (cos(x))^2), %0.6f,%0.6f,%d\n", low, high, partition);
    }
    // print The subsequent lines looks like: <partition>,<value>
    for (uint32_t x = 2; x <= partition; x += 2) {
        if (a_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&a, low, high, x));
        } else if (b_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&b, low, high, x));
        } else if (c_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&c, low, high, x));
        } else if (d_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&d, low, high, x));
        } else if (e_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&e, low, high, x));
        } else if (f_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&f, low, high, x));
        } else if (g_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&g, low, high, x));
        } else if (h_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&h, low, high, x));
        } else if (i_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&i, low, high, x));
        } else if (j_integrate) {
            printf("%d,%0.15lf\n", x, integrate(&j, low, high, x));
        }
    }
}
