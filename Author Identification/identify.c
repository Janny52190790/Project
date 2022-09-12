#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "metric.h"
#include "node.h"
#include "parser.h"
#include "pq.h"
#include "salts.h"
#include "speck.h"
#include "text.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define OPTION "d:k:n:l:emcv"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "Identifies the author of some anonymous text passed through stdin.\n"
        "Basically computes k-nearest neighbors, where k = 1 by default.\n"
        "The number of noise words that are removed is tunable.\n"
        "Uses either Euclidean, Manhattan, or cosine distance as metric.\n"
        "USAGE\n"
        "%s [d:K:n:l:emcv] [-d database] [-k matches] [-n noisefile] [-l limit]\n"
        "\n"
        "OPENTIONS\n"
        "-d database     Database of authors and texts [default: lib.db]\n"
        "-k matches      Set number of top matches to display [default: 5]\n"
        "-n noisefile    Set file of words to ignore [default: noise.txt]\n"
        "-l limit        Set noise word limit [default: 100]\n"
        "-e              Set distance metric as Euclidean distance [default]\n"
        "-m              Set distance metric as Manhattan distance\n"
        "-c              Set distance metric as cosine distance\n"
        "-v              Enable verbose printing of program run\n"
        "-h              Display program help and usage\n",
        exec);
}

int main(int argc, char **argv) {
    FILE *database = fopen("lib.db", "r");
    FILE *noise = fopen("noise.txt", "r");
    uint32_t matches = 5;
    uint32_t noise_words = 100;
    Metric distance = EUCLIDEAN;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTION)) != -1) {
        switch (opt) {
        case 'd': database = fopen(optarg, "r"); break;
        case 'o': noise = fopen(optarg, "r"); break;
        case 'k': matches = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'l': noise_words = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'e': distance = EUCLIDEAN; break;
        case 'm': distance = MANHATTAN; break;
        case 'c': distance = COSINE; break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }
    FILE *anonymous = stdin;

    noiselimit = noise_words;
    Text *noisetext = text_create(noise, NULL); // create a noise file
    Text *a = text_create(anonymous, noisetext);

    char num[100];
    fgets(num, 100, database);
    num[strcspn(num, "\n")] = 0;
    uint32_t n = atoi(num);

    PriorityQueue *q = pq_create(n);

    char name[200];
    char path[500];
    FILE *authorpath = 0;
    double distances;
    Text *p;
    while (fgets(name, 200, database) != NULL && fgets(path, 500, database) != NULL) {
        name[strcspn(name, "\n")] = 0;
        //printf("%s\n", name);
        path[strcspn(path, "\n")] = 0;
        //printf("%s\n", path);
        if (access(path, F_OK) == 0) {
            //printf("Yes");
            authorpath = fopen(path, "r");
        } else {
            continue;
        }
        p = text_create(authorpath, noisetext);
        distances = text_dist(a, p, distance);
        //printf("%0.15f\n", distance);
        //printf("%s\n", name);
        enqueue(q, name, distances);
        //pq_print(q);
    }
    //pq_print(q);
    char *dis;
    if (distance == EUCLIDEAN) {
        dis = "Euclidean distance";
    } else if (distance == MANHATTAN) {
        dis = "Manhattan distance";
    } else {
        dis = "Cosine distance";
    }

    char *author;
    double dist;
    printf("Top %d, metric: %s, noise limit: %d\n", matches, dis, noise_words);
    for (uint32_t i = 0; i < matches; i++) {
        dequeue(q, &author, &dist);
        printf("%d) %s [%0.15f]\n", i + 1, author, dist);
    }

    fclose(database);
    fclose(noise);
    fclose(anonymous);
    fclose(authorpath);
    pq_delete(&q);
    text_delete(&a);
    text_delete(&p);
    text_delete(&noisetext);
    return 0;
}
