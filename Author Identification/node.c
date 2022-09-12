#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "node.h"

Node *node_create(char *word) {
    // The constructor for a node.
    Node *n = (Node *) malloc(sizeof(Node));
    assert(n);
    char *copy = strdup(word);
    n->word = copy;
    n->count = 0;
    return n;
}

void node_delete(Node **n) {
    // The destructor for a node.
    free(*n);
    *n = NULL;
    return;
}

void node_print(Node *n) {
    // A debug function to print out the contents of a node.
    if (n != NULL) {
        printf("node is %s, %u\n", n->word, n->count);
    }
    return;
}
