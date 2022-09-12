#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"
#include "stack.h"

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    //The constructor for a stack. The maximum number of nodes the stack can hold is specified by capacity.
    Stack *s = (Stack *) malloc(sizeof(Stack));
    assert(s);
    s->capacity = capacity;
    s->top = 0;
    s->items = (Node **) malloc((capacity) * sizeof(Node *));
    return s;
}

void stack_delete(Stack **s) {
    // The destructor for a stack. Remember to set the pointer to NULL after you free the memory allocated by the stack.
    free((*s)->items);
    (*s)->items = NULL;
    free(*s);
    *s = NULL;
    return;
}

bool stack_empty(Stack *s) {
    // Returns true if the stack is empty and false otherwise.
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool stack_full(Stack *s) {
    // Returns true if the stack is full and false otherwise.
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    // Returns the number of nodes in the stack.
    if (s->top > 256) {
        printf("too large");
        return 0;
    } else {
        return (s->top);
    }
}

bool stack_push(Stack *s, Node *n) {
    // Pushes a node onto the stack.
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top = s->top + 1;
        return true;
    }
}

bool stack_pop(Stack *s, Node **n) {
    // Pops a node off the stack, passing it back through the double pointer n.
    if (!stack_empty(s)) {
        s->top = s->top - 1;
        *n = s->items[s->top];
        return true;
    } else {
        return false;
    }
}

void stack_print(Stack *s) {
    // A debug function to print the contents of a stack.
    for (uint32_t i = 0; i < s->top; i++) {
        node_print(s->items[i]);
    }
    return;
}
