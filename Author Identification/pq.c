#include "pq.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//priority queue is cited from asgn3 and asgn6
//pseudocode is from asgn3's PDF

typedef struct PQNode {
    // ADT to create a node which contains author and distance
    char *author;
    double dist;
} PQNode;

typedef struct PriorityQueue {
    // ADT for PriorityQueue
    uint32_t top;
    uint32_t capacity;
    PQNode **pn;
} PriorityQueue;

PQNode *pqnode_create(char *author, double dist) {
    // he constructor for a PQNode that holds up to capacity elements.
    PQNode *pqn = (PQNode *) malloc(sizeof(PQNode));
    assert(pqn);
    char *copy = strdup(author);
    pqn->author = copy;
    pqn->dist = dist;
    return pqn;
}

void pqnode_delete(Node **pqn) {
    // The destructor for a PQNode
    free(*pqn);
    *pqn = NULL;
    return;
}

void pqnode_print(PQNode *n) {
    // A debug function to print the PQNode
    if (n != NULL) {
        printf("pqnode is %s, %0.15f\n", n->author, n->dist);
    }
    return;
}

PriorityQueue *pq_create(uint32_t capacity) {
    // The constructor for a priority queue that holds up to capacity elements.
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    assert(q);
    q->capacity = capacity;
    q->top = 0;
    q->pn = (PQNode **) malloc(capacity * sizeof(PQNode *));
    return q;
}

void pq_delete(PriorityQueue **q) {
    // The destructor for a priority queue.
    free((*q)->pn);
    free(*q);
    *q = NULL;
    return;
}

bool pq_empty(PriorityQueue *q) {
    // Returns true if the priority queue is empty and false otherwise.
    if (q->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    // Returns true if the priority queue is full and false otherwise.
    if (q->top == q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    // Returns the number of elements in the priority queue.
    return q->top;
}

// do Heap Sort
// the idea is from asgn3 code.
uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if ((right <= last) && (q->pn[right - 1]->dist < q->pn[left - 1]->dist)) {
        return right;
    }
    return left;
}

// the idea is from asgn3 code.
void fix_heap(PriorityQueue *q, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = min_child(q, mother, last);

    while (mother <= last / 2 && (!found)) {
        if (q->pn[great - 1]->dist < q->pn[mother - 1]->dist) {
            PQNode *temp = q->pn[mother - 1];
            q->pn[mother - 1] = q->pn[great - 1];
            q->pn[great - 1] = temp;
            mother = great;
            great = min_child(q, mother, last);
        } else {
            found = true;
        }
    }
}

// not sure whether we need heap_sort function

// the idea is from asgn3 code.
bool enqueue(PriorityQueue *q, char *author, double dist) {
    // Enqueue the author, dist pair into the priority queue.
    PQNode *n = pqnode_create(author, dist);
    // create a node contain authoe and dist
    if (pq_full(q)) {
        free(n);
        return false;
    }
    //q->top = q->top + 1;
    q->pn[q->top++] = n;
    //q->top = q->top + 1;
    // build heap
    for (uint32_t father = q->top / 2; father > 0; father--) {
        fix_heap(q, father, q->top);
    }
    return true;
}

// the idea is from asgn3 code.
bool dequeue(PriorityQueue *q, char **author, double *dist) {
    // Dequeue the author, dist pair from the priority queue.
    //Node **n;
    if (pq_empty(q)) { // pq_empty(q)
        return false;
    }
    *author = q->pn[0]->author;
    *dist = q->pn[0]->dist;
    //q->top = q->top - 1;
    q->pn[0] = q->pn[--(q->top)];
    //q->top = q->top - 1;
    // build heap aganin
    for (uint32_t father = q->top / 2; father > 0; father--) {
        fix_heap(q, father, q->top);
    }
    return true;
}

// the idea is from asgn3 code.
void pq_print(PriorityQueue *q) {
    // A debug function to print the priority queue.
    for (uint32_t i = 0; i < q->top; i++) {
        pqnode_print(q->pn[i]);
    }
}
