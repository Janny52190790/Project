#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

Node *node_create(uint8_t symbol, uint64_t frequency) {
    // The constructor for a node.
    Node *n = (Node *) malloc(sizeof(Node));
    assert(n);
    n->symbol = symbol;
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void node_delete(Node **n) {
    // The destructor for a node.
    free(*n);
    *n = NULL;
    free(n);
    n = NULL;
    return;
}

Node *node_join(Node *left, Node *right) {
    // Joins a left child node and right child node, returning a pointer to a created parent node.
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

void node_print(Node *n) {
    // A debug function to verify that your nodes are created and joined correctly.
    if (n != NULL) {
        node_print(n->left);
        node_print(n->right);
        if (n->left == NULL && n->right == NULL) {
            printf("lead Node:%c, %lu\n", n->symbol, n->frequency);
        } else {
            printf("Parent Node:%c, %lu\n", n->symbol, n->frequency);
        }
    }
    return;
}
