#include "node.h"
#include "salts.h"
#include "speck.h"
#include "ht.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
// hash table is cited from professor Long's lecture slide.

struct HashTableIterator {
    HashTable *table; // The hash table to iterate over.
    uint32_t slot; // The current slot the iterator is on.
};

struct HashTable {
    uint64_t salt[2]; // The salt to use for the hash function.
    uint32_t size; // The number of slots in the hash table.
    Node **slots; // The array of hash table items.
};

HashTable *ht_create(uint32_t size) {
    //The constructor for a hash table. The size parameter denotes the number of slots that the hash table can index up to. The salt for the hash table is provided in salts.h.
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    assert(ht);
    ht->size = size;
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    ht->slots = (Node **) calloc(size, sizeof(Node *));
    return ht;
}

void ht_delete(HashTable **ht) {
    // The destructor for a hash table. This should free any remaining nodes left in the hash table.
    free((*ht)->slots);
    (*ht)->slots = NULL;
    free(*ht);
    *ht = NULL;
    return;
}

uint32_t ht_size(HashTable *ht) {
    //Returns the hash table’s size, the number of slots it can index up to.
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *word) {
    // Searches for an entry, a node, in the hash table that contains word.
    uint32_t count = 0;
    uint32_t index = hash(ht->salt, word) % ht_size(ht);
    while (count < ht->size) {
        Node *n = ht->slots[index];
        if (n && (strcmp(n->word, word) == 0)) {
            return n;
        }
        index = (index + 1) % ht_size(ht);
        count = count + 1;
    }
    Node *n = NULL;
    return n;
}

Node *ht_insert(HashTable *ht, char *word) {
    // Inserts the specified word into the hash table.
    uint32_t count = 0;
    uint32_t index = hash(ht->salt, word) % ht_size(ht);
    //printf("%d\n", index);
    Node *n = NULL;
    while (count < ht->size) {
        //printf("Yes\n");
        if (ht->slots[index] == 0) {
            n = node_create(word);
            ht->slots[index] = n;
            n->count = n->count + 1;

            return n;
        } else if (strcmp(ht->slots[index]->word, word) == 0) {
            n = ht->slots[index];
            n->count = n->count + 1;
            return n;
        }
        index = (index + 1) % ht_size(ht);
        count = count + 1;
    }
    return n;
}

void ht_print(HashTable *ht) {
    // A debug function to print out the contents of a hash table.
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        node_print(ht->slots[i]);
    }
    return;
}

HashTableIterator *hti_create(HashTable *ht) {
    // Creates a new hash table iterator.
    HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));
    hti->slot = 0;
    hti->table = ht;
    return hti;
}

void hti_delete(HashTableIterator **hti) {
    // Deletes a hash table iterator.
    free(*hti);
    *hti = NULL;
}

Node *ht_iter(HashTableIterator *hti) {
    // Returns the pointer to the next valid entry in the hash table.
    static uint32_t htiindex = 0;
    if (htiindex == hti->table->size) {
        Node *n = NULL;
        htiindex = 0;
        return n;
    } else if (hti->table->slots[htiindex] != NULL) {
        Node *n = hti->table->slots[htiindex];
        hti->slot = hti->slot + 1;
        htiindex = htiindex + 1;
        return n;
    } else {
        while (htiindex < hti->table->size) {
            if (hti->table->slots[htiindex] != NULL) {
                Node *n = hti->table->slots[htiindex];
                hti->slot = hti->slot + 1;
                htiindex = htiindex + 1;
                return n;
            }
            hti->slot = hti->slot + 1;
            htiindex = htiindex + 1;
        }
    }
    Node *n = NULL;
    htiindex = 0;
    return n;
}
