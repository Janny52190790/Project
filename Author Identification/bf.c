#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "salts.h"
#include "bf.h"
#include "bv.h"
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt.
    uint64_t secondary[2]; // Secondary hash function salt.
    uint64_t tertiary[2]; // Tertiary hash function salt.
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    // The constructor for a Bloom filter.
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    assert(bf);
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    bf->filter = bv_create(size);
    return bf;
}

void bf_delete(BloomFilter **bf) {
    // The destructor for a Bloom filter.
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    // Returns the size of the Bloom filter.
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *word) {
    // Takes word and inserts it into the Bloom filter.
    uint32_t index1 = hash(bf->primary, word) % bf_size(bf); // uint32_t
    bv_set_bit(bf->filter, index1);
    uint32_t index2 = hash(bf->primary, word) % bf_size(bf);
    bv_set_bit(bf->filter, index2);
    uint32_t index3 = hash(bf->primary, word) % bf_size(bf);
    bv_set_bit(bf->filter, index3);
    return;
}

bool bf_probe(BloomFilter *bf, char *word) {
    // Probes the Bloom filter for word. Like with bf_insert(), word is hashed with each of the three salts for three indices.
    uint32_t index1 = hash(bf->primary, word) % bf_size(bf);
    uint32_t index2 = hash(bf->primary, word) % bf_size(bf);
    uint32_t index3 = hash(bf->primary, word) % bf_size(bf);
    if (bv_get_bit(bf->filter, index1) && bv_get_bit(bf->filter, index2)
        && bv_get_bit(bf->filter, index3)) {
        return true;
    } else {
        return false;
    }
}

void bf_print(BloomFilter *bf) {
    // A debug function to print out the bits of a Bloom filter.
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
            printf("1");
        } else if (bv_get_bit(bf->filter, i) == 0) {
            printf("0");
        }
    }
    printf("\n");
    return;
}
