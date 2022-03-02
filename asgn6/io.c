#include <stdio.h>
#include <stdlib.h>
#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
// io.c

uint64_t bytes_read;
uint64_t bytes_written;
static uint8_t buf[BLOCK] = { 0 };
static int indexb = 0;
static ssize_t bw;
static uint8_t buffer = 0; // init the buf
static uint8_t indexbit = 0;
static ssize_t br;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    // he number of bytes that were read from the input file descriptor, infile, is returned.
    ssize_t bytesr = 0;
    int64_t bytesread = 0;
    while ((bytesr = read(infile, buf, nbytes - bytesread)) > 0) {
        bytesread = bytes_read + bytesr;
        if (bytesread == nbytes) {
            break;
        }
    }
    return bytesread;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    // The number of bytes written out to the output file descriptor, outfile, is returned.
    ssize_t bytesw;
    int64_t bytes_w = 0;
    while ((bytesw = write(outfile, buf, nbytes - bytes_w)) > 0) {
        bytes_w = bytes_w + bytesw;
        if (bytes_w == nbytes) {
            break;
        }
    }
    return bytes_w;
}

bool read_bit(int infile, uint8_t *bit) {
    // read a single bit from a file.
    if ((indexbit % 8) == 0) {
        br = read_bytes(infile, &buffer, 1);
    }
    if (br == 0) {
        return false;
    }
    *bit = (buffer >> (indexbit % 8) & 1);
    indexbit = indexbit + 1;
    return true;
}
// cite the idea is from Audrey tutor section on 2/26

void write_code(int outfile, Code *c) {
    // write buffer if bits into the outfile.
    /*if(indexb / 8 == BLOCK){
		bw = write_bytes(outfile, buf, BLOCK);
		indexb = 0;
	}*/
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (code_get_bit(c, i) == 0) {
            buf[indexb / 8] &= ~(1 << indexb % 8);
        } else {
            buf[indexb / 8] |= (1 << indexb % 8);
        }
        indexb = indexb + 1;

        if (indexb / 8 == BLOCK) {
            bw = write_bytes(outfile, buf, BLOCK);
            indexb = 0;
        }
    }
    return;
}

// get the instruction from Miles section.
void flush_codes(int outfile) {
    // write out any leftover, buffered bits.
    if (indexb != BLOCK * 8) {
        while (indexb % 8 - 1 != 0) {
            buf[indexb / 8] &= ~(1 << indexb % 8);
            indexb = indexb + 1;
        }
        write_bytes(outfile, buf, indexb / 8 + 1);
        return;
    }
}
