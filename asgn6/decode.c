#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "huffman.h"
#include "defines.h"
#include "header.h"
#include "code.h"
#include "io.h"
#include "pq.h"
#include "node.h"
#include "stack.h"
// decode.c

#define OPTION "i:o:v"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This decoder will read in a compressed input file and decompress it, expanding it back "
        "to its original, uncompressed size. \n"
        "\n"
        "USAGE\n"
        "   %s [hi:o:v] [-i input] [-o output] [-v compression]\n"
        "\n"
        "OPENTIONS\n"
        "   -h: Prints out a help message.\n"
        "   -i: Specifies the input file to encode using Huffman coding. The default input should "
        "be set as stdin.\n"
        "   -o: Specifies the output file to write the compressed input to. The default output "
        "should be set as stdout.\n"
        "   -v: Prints compression statistics to stderr.\n",
        exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    int input = STDIN_FILENO; //file descriptor for stdin
    int output = STDOUT_FILENO; //file descripter for stdout
    bool compression = false;
    while ((opt = getopt(argc, argv, OPTION)) != -1) {
        switch (opt) {
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600); break;
        case 'v': compression = true; break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    Header head;
    read_bytes(input, (uint8_t *) &head, sizeof(head)); // how to read the header

    if (head.magic != MAGIC) {
        printf("magic is wrong");
        return 1;
    }

    head.permissions = 0600;
    fchmod(output, 0600); //how to set the permission?

    uint8_t *tree_dump;
    tree_dump = (uint8_t *) malloc(head.tree_size * sizeof(uint8_t));
    uint16_t readsize = read_bytes(input, tree_dump, head.tree_size);
    //Read the dumped tree from infile into an array that is tree_size bytes long.

    Node *root = rebuild_tree(readsize, tree_dump);

    Node *n = root;
    uint8_t bit = 0;
    uint64_t indexb = 0;
    uint8_t bbuffer[256] = { 0 };
    int bytecount = 0;
    while (read_bit(input, &bit)) {
        if (bit == 1) {
            n = n->right;
        } else {
            n = n->left;
        }

        if (n->right == NULL && n->left == NULL) {
            if (indexb != head.file_size) {
                bbuffer[indexb] = n->symbol;
                indexb = indexb + 1;
            } else {
                break;
            }
            n = root;
            if (indexb >= 256) {
                write_bytes(output, bbuffer, indexb);
                bytecount = bytecount + 1;
                indexb = 0;
            }
        }
    }
    indexb = head.file_size - bytecount * 256;
    ;
    write_bytes(output, bbuffer, indexb);

    struct stat buffer;
    int status;
    status = fstat(output, &buffer);

    if (compression) {
        printf("file size: %lu bytes\n", head.file_size);
        printf("compressed file size: %d bytes\n", status);
        printf("space saving: %.2lu", 100 * (1 - (head.file_size / status)));
    }

    close(input);
    close(output);
    return 0;
}
