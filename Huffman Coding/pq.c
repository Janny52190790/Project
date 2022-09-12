#include "node.h"
#include "pq.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct PriorityQueue {
    uint32_t rear;
    uint32_t size; // circular queue
    uint32_t front;
    uint32_t capacity;
    Node **pn;
};

PriorityQueue *pq_create(uint32_t capacity) {
    // The constructor for a priority queue.
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    q->rear = 0;
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->pn = (Node **) malloc(capacity * sizeof(Node *));
    return q;
}

void pq_delete(PriorityQueue **q) {
    // The destructor for a priority queue.
    free((*q)->pn);
    (*q)->pn = NULL;
    free(*q);
    *q = NULL;
    return;
}

bool pq_empty(PriorityQueue *q) {
    // Returns true if the priority queue is empty and false otherwise.
    if (q->size == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    // Returns true if the priority queue is full and false otherwise.
    if (q->size == q->capacity) { // size
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    // Returns the number of items currently in the priority queue.
    q->size = ((q->capacity - q->front) + q->rear) % (q->capacity);
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    // Enqueues a node into the priority queue.
    static uint32_t size;
    if (pq_full(q)) {
        return false;
    } else if (pq_size(q) == 0) {
        q->pn[q->rear] = n;
        //node_print(n);
        q->rear = (q->rear + 1) % q->capacity;
        size = 1;
        return true;
    } else {
        for (uint32_t i = 0; i < size; i++) {
            if (n->frequency < q->pn[(i + q->capacity) % q->capacity]->frequency) {
                for (uint32_t j = size; j > i; j--) {
                    q->pn[j] = q->pn[j - 1];
                }
                q->pn[i] = n;
                q->rear = (q->rear + 1) % q->capacity;
                size = size + 1;
                return true;
            } else {
                continue;
            }
        }
        q->pn[q->rear] = n;
        //node_print(n);
        q->rear = (q->rear + 1) % q->capacity;
        size = size + 1;
        return true;
    }
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    // Dequeues a node from the priority queue, passing it back through the double pointer n.
    if (pq_empty(q)) {
        return false;
    } else {
        *n = q->pn[q->front];
        // cite Audrey tutor section on Wednesday 2/17.
        q->front = (q->front + 1) % q->capacity;
        return true;
    }
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = q->front; i <= q->size; i++) {
        node_print(q->pn[i]);
    }
    return;
}
