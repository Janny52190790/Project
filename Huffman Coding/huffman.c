#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "node.h"
#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "pq.h"
#include "stack.h"

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Constructs a Huffman tree given a computed histogram.
    PriorityQueue *q = pq_create(ALPHABET);
    Node *right;
    Node *left;
    Node *parent;
    for (int histindex = 0; histindex < ALPHABET; histindex++) {
        if (hist[histindex] == 0) {
            continue;
        } else {
            Node *n = node_create(histindex, hist[histindex]);
            if (!enqueue(q, n)) {
                printf("full priority queue.");
                return 0;
            }
        }
    }
    while (pq_size(q) > 1) {
        if (dequeue(q, &left)) {
            if (dequeue(q, &right)) {
                parent = node_join(left, right);
                if (!enqueue(q, parent)) {
                    printf("full priority queue.");
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    dequeue(q, &parent);
    pq_delete(&q);
    return parent;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //Populates a code table, building the code for each symbols in the Huffman tree.
    static Code c;
    uint8_t bit = 0;
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, &bit);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &bit);
        }
    }
    return;
}

void dump_tree(int outfile, Node *root) {
    //Conducts a post-order traversal of the Huffman tree rooted at root, writing it to outfile.
    // postorder
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (root->left == NULL && root->right == NULL) {
            char buf[] = "L";
            write(outfile, buf, 1);
            write(outfile, &root->symbol, 1);
        } else {
            char buf[] = "I";
            write(outfile, buf, 1);
        }
    }
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    //Reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump.
    Stack *s = stack_create(nbytes); // stack of nodes
    Node *nright;
    Node *nleft;
    Node *n;
    Node *root;
    int i = 0;
    while (i < nbytes) {
        if (tree_dump[i] == 'L') {
            n = node_create(tree_dump[i + 1], 0);
            if (!stack_push(s, n)) {
                return 0;
            }
            i = i + 2;
        } else if (tree_dump[i] == 'I') {
            stack_pop(s, &nright);
            stack_pop(s, &nleft);
            Node *parent = node_join(nleft, nright);
            stack_push(s, parent);
            i = i + 1;
        }
    }
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {
    // The destructor for a Huffman tree.
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        if ((*root)->left == NULL && (*root)->right == NULL) {
            node_delete(&(*root));
        }
        node_delete(root);
    }
    return;
}
