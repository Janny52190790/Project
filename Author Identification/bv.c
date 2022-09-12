#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bv.h"

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // The constructor for a bit vector that holds length bits.
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    assert(bv);
    bv->length = length;
    int kbyte = length / 8;
    int kbit = length % 8;
    bv->vector = (uint8_t *) calloc((kbyte + kbit), sizeof(uint8_t));
    if (!bv->vector) {
        free(bv);
        return NULL;
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    // The destructor for a bit vector.
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    // Returns the length of a bit vector.
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    // Sets the ith bit in a bit vector.
    if (i < bv_length(bv)) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        bv->vector[kbyte] = (1 << kbit) | bv->vector[kbyte];
        return true;
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // Clears the ith bit in the bit vector.
    if (i < bv_length(bv)) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        bv->vector[kbyte] = ~(1 << kbit) & bv->vector[kbyte];
        return true;
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    // Returns the ith bit in the bit vector.
    if (i < bv_length(bv)) {
        int kbyte = i / 8; // the byte index
        int kbit = i % 8; // the bit index
        return ((bv->vector[kbyte] & (1 << kbit)) != 0);
    } else {
        return 0;
    }
}

void bv_print(BitVector *bv) {
    // A debug function to print the bits of a bit vector.
    for (uint32_t i = 0; i < bv_length(bv); i++) {
        printf("%d", bv_get_bit(bv, i));
    }
    printf("\n");
    return;
}
