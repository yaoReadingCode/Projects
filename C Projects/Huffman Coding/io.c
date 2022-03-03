#include "io.h"

#include "defines.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t buf[BLOCK] = { 0 };

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes = 0; // bytes read per loop
    int total = 0; // total bytes read so far
    while (
        ((bytes = read(infile, buf, (nbytes - bytes))) > 0)
        && (total
            != nbytes)) { // loops if bytes read in previous loop is not = 0 and total bytes read is not = nbytesi
        total += bytes; // adds bytes to total number of bytes written
        if (bytes == -1) {
            fprintf(stderr, "Failed to read bytes.\n");
            exit(1);
        }
    }
    return total; // returns total bytes read
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes = 0; // bytes written per loop
    int total = 0; // total bytes written so far
    while (
        ((bytes = write(outfile, buf, (nbytes - bytes))) > 0)
        && (total
            != nbytes)) { // loops if bytes written in previous loop is not = 0 and total bytes written is not = nbytes
        total += bytes; // adds bytes to total number of bytes written
        //nbytes = nbytes - total; // subtracts total written so far from nbytes
        //buf += bytes; 			// what is this?
    }
    //return bytes; // return total bytes read
    return total;
}

//if (verbose) {
//          fprintf(stderr, "Uncompressed file size: %" PRIu64 "\nCompressed file size: %" PRIu64 "\nSpace saving: %" PRIu64 "\n", ufs, cfs, ss);
//  }

static int bit_index = 0; // index of where bit is in buffer

bool read_bit(int infile, uint8_t *bit) {
    int end = 0; // initalize end of buffer and totals bytes
    int bytes = 0;
    if ((bit_index == (BLOCK * 8))
        || (bit_index == 0)) { // if bit index is at end or beginning of buffer
        bit_index = 0; // set bit index back to 0
        bytes = read_bytes(
            infile, buf, BLOCK); // fill buffer back again with bytes and set bytes equal to that
        if (bytes < BLOCK) { // if bytes read is less than block bytes
            end = (8 * bytes) + 1; // set end to bytes 		// possible error?
        }
    }
    *bit = ((buf[(bit_index) / 8] & (1 << ((bit_index) % 8)))
            >> ((bit_index) % 8)); // set bit to bit in buffer		// possible error?
    bit_index = (bit_index + 1); // add 1 to bit index
    if (bit_index == end) { // if all bits read
        return false; // return false
    } else {
        return true; // else true
    }
}

int buf_index = 0; // index of where bit is in buffer

void write_code(int outfile, Code *c) { // possible error
    for (uint32_t i = 0; i < code_size(c); i++) { // write bit from code to buffer
        if (((c->bits[i / 8] & (1 << (i % 8))) >> (i % 8))
            == 1) { // if bit in code is 1 set bit in buffer to 1
            buf[buf_index / 8] |= (1 << (buf_index % 8));
        } else { // if bit in code is 0 set bit in buffer to 1
            buf[buf_index / 8] &= ~(1 << (buf_index % 8));
        }
        buf_index = (buf_index + 1) % (BLOCK * 8); // add 1 to bit index
        if (buf_index == (BLOCK * 8)) { // if bit index reached max buffer size
            write_bytes(outfile, buf, BLOCK); // write to buffer again
            buf_index = 0; // set index to 0
            memset(buf, 0, BLOCK);
        }
    }
    return;
}

void flush_codes(int outfile) {
    // writes out remaining bits in buffer by getting remaining bits, converting that to bytes and putting that in the write byte function
    int nbytes;
    int a = buf_index / 8;
    if (buf_index > (2 * a)) {
        nbytes = (buf_index / 8) + 1;
    } else {
        nbytes = (buf_index / 8);
    }
    if (buf_index > 0) {
        write_bytes(outfile, buf, nbytes); // checks this
    }
    return;
}
