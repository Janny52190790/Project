#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "code.h"
#include <math.h>

Code code_init(void) {
    // create a new Code on the stack, setting top to 0, and zeroing out the array of bits, bits.
    Code c;
    c.top = 0;
    for (int i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    // Returns the size of the Code, which is exactly the number of bits pushed onto the Code.
    return c->top;
}

bool code_empty(Code *c) {
    // Returns true if the Code is empty and false otherwise.
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    // Returns true if the Code is full and false otherwise.
    if (c->top >= (MAX_CODE_SIZE - 1)) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    // Sets the bit at index i in the Code, setting it to 1.
    if (!code_full(c)) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        c->bits[kbyte] = (1 << kbit) | c->bits[kbyte];
        return true;
    } else {
        return false;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    // Clears the bit at index i in the Code, clearing it to 0.
    if (!code_empty(c)) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        c->bits[kbyte] = ~(1 << kbit) & c->bits[kbyte];
        return true;
    } else {
        return false;
    }
}

// cite the idea from Miles section.
bool code_get_bit(Code *c, uint32_t i) {
    // Gets the bit at index i in the Code.
    if (i < ALPHABET) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        return ((c->bits[kbyte] & (1 << kbit)) != 0);
    } else {
        return 0;
    }
}

// cite the idea from Miles section.
bool code_push_bit(Code *c, uint8_t bit) {
    // Pushes a bit onto the Code.
    if (!code_full(c)) {
        // now the total bits are c->bits,
        if (bit == 1) {
            code_set_bit(c, c->top);
        } else {
            code_clr_bit(c, c->top);
        }
        c->top = c->top + 1;
        return true;
    } else {
        return false;
    }
}

// cite the idea from Miles section.
bool code_pop_bit(Code *c, uint8_t *bit) {
    // Pops a bit off the Code.
    if (!code_empty(c)) {
        //c->top = c->top - 1;
        //*bit = code_get_bit(c, c->top);
        if (code_get_bit(c, c->top)) {
            *bit = 1;
        } else {
            *bit = 0;
        }

        c->top = c->top - 1;
        //printf("%d\n", c->top);
        return true;
    } else {
        return false;
    }
}

void code_print(Code *c) {
    // A debug function
    for (uint32_t j = 0; j < c->top; j++) {
        if (code_get_bit(c, j)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    return;
}
