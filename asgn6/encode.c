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

// encode.c
#define OPTION "i:o:v"

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This encoder will read in an input ile, find the Huffman encoding of its contents, and "
        "use the encoding to compress the file.\n"
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
    int input = STDIN_FILENO; //file descriptor for stdin
    int output = STDOUT_FILENO; //file descripter for stdout
    bool compression = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTION)) != -1) {
        switch (opt) {
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600); break;
        case 'v': compression = true; break;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    if (lseek(input, 0, SEEK_SET) < 0) {
        input = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
    }

    uint64_t hist[256] = { 0 }; // ASCII + Extended ASCII.
    hist[0] = 1;
    hist[255] = 1;

    int infilebytes;
    uint8_t buf[256];
    do {
        infilebytes = read_bytes(input, buf, 256);
        for (int i = 0; i < infilebytes; i++) {
            int num = buf[i];
            hist[num] = hist[num] + 1;
        }
    } while (infilebytes == 256);
    // Increment the count of element 0 and element 255 by one

    Node *n = build_tree(hist);
    // Construct the Huffman tree using a priority queue

    Code table[256]; // Code table[static ALPHABET]
    build_codes(n, table);

    // Construct a header.
    Header head;
    // Header *head = (Header *)malloc(sizeof(Header));
    head.magic = MAGIC;
    head.permissions = 0600;
    fchmod(output, 0600);
    //  how to use fstate and fchmod
    int treel = 0;
    int histindex = 0;
    while (histindex < 256) { // 256 is ALPHABE
        if (hist[histindex] == 0) {
            histindex = histindex + 1;
        } else {
            treel = treel + 1;
            histindex = histindex + 1;
        }
    }

    head.tree_size = (3 * treel) - 1; // how to calculate the unique symbols.
    struct stat fs;
    fstat(input, &fs);
    head.file_size = fs.st_size; // what is the output file size

    write_bytes(output, (uint8_t *) &head,
        sizeof(head)); // wo first write the header and return bytes_written

    dump_tree(output, n);

    lseek(input, 0, SEEK_SET);
    uint8_t buffer[256];
    int inbytes;
    do {
        inbytes = read_bytes(input, buffer, 256);
        //printf("inbytes = %d\n", inbytes);
        for (int i = 0; i < inbytes; i++) {
            uint8_t r = buffer[i];
            write_code(output, &table[r]);
        }
    } while (inbytes == 256);
    flush_codes(output);

    struct stat buff;
    int status;
    status = fstat(output, &buff);
    if (compression) {
        printf("file size: %lu bytes\n", head.file_size);
        printf("compressed file size: %d bytes\n", status);
        printf("space saving: %.2lu", 100 * (1 - (head.file_size / status)));
    }

    close(input);
    close(output);
    return 0;
}
