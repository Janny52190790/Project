#include "ht.h"
#include "bf.h"
#include "parser.h"
#include "metric.h"
#include "speck.h"
#include "text.h"
#include <assert.h>
#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WORD "[a-zA-Z]+(['-][a-zA-Z]+)*" //[a-zA-Z]+(('|-)[a-zA-Z]+)*
uint32_t noiselimit;

struct Text {
    //The constructor for a text.
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};

//cite Audrey's section on 3/9 the detail is in the DESIION.pdf
Text *text_create(FILE *infile, Text *noise) {
    // Deletes a text.
    Text *text = (Text *) malloc(sizeof(Text));
    assert(text);
    text->ht = ht_create(524288);
    text->bf = bf_create(2097152);
    text->word_count = 0;
    regex_t re;
    regcomp(&re, WORD, REG_EXTENDED);
    char *word;
    while ((word = next_word(infile, &re))) {
        if ((noise == NULL) && (text->word_count == noiselimit)) {
            break;
        }
        int i = 0;
        while (word[i]) {
            word[i] = tolower(word[i]);
            i++;
        }
        if (!text_contains(noise, word)) {
            text->word_count = text->word_count + 1;
            ht_insert(text->ht, word);
            bf_insert(text->bf, word);
        }
    }
    regfree(&re);
    return text;
}

void text_delete(Text **text) {
    // Deletes a text.
    bf_delete(&(*text)->bf);
    ht_delete(&(*text)->ht);
    free(*text);
    *text = NULL;
}

double text_dist(Text *text1, Text *text2, Metric metric) {
    // This function returns the distance between the two texts depending on the metric being used.
    double distance = 0;
    Node *t;
    HashTableIterator *hti1 = hti_create(text1->ht);
    HashTableIterator *hti2 = hti_create(text2->ht);
    while ((t = ht_iter(hti1)) != NULL) {
        double text1_freq = text_frequency(text1, t->word);
        double text2_freq = text_frequency(text2, t->word);
        if (metric == EUCLIDEAN) {
            double d = fabs(text1_freq - text2_freq);
            distance = distance + pow(d, 2);
        } else if (metric == MANHATTAN) {
            double d = fabs(text1_freq - text2_freq);
            distance = distance + d;
        } else if (metric == COSINE) {
            double d = text1_freq * text2_freq;
            distance = distance + d;
        }
    }
    while ((t = ht_iter(hti2)) != NULL) {
        if (!text_contains(text1, t->word)) {
            double text2_freq = text_frequency(text2, t->word);
            if (metric == EUCLIDEAN) {
                distance = distance + pow(text2_freq, 2);
            } else if (metric == MANHATTAN) {
                distance = distance + text2_freq;
            }
        } else {
            continue;
        }
    }

    if (metric == EUCLIDEAN) {
        distance = sqrt(distance);
    } else if (metric == COSINE) {
        distance = 1 - distance;
    }
    hti_delete(&hti1);
    node_delete(&t);
    return distance;
}

double text_frequency(Text *text, char *word) {
    // Returns the frequency of the word in the text.
    if (text_contains(text, word)) {
        Node *n = ht_lookup(text->ht, word);
        double freq = (double) n->count / (double) text->word_count;
        return freq;
    } else {
        double freq = 0;
        return freq;
    }
}

bool text_contains(Text *text, char *word) {
    // Returns whether or not a word is in the text.
    if (text == NULL) {
        return false;
    } else if (bf_probe(text->bf, word)) {
        Node *w = ht_lookup(text->ht, word);
        if (w != NULL) {
            return true;
        }
    }
    return false;
}

void text_print(Text *text) {
    // A debug function to print the contents of a text.
    ht_print(text->ht);
    bf_print(text->bf);
    printf("the word count is %d\n", text->word_count);
}
