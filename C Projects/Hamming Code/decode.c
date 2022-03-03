#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int uc = 0;
int crr = 0;

int main(int argc, char **argv) {
    FILE *infile
        = stdin; // intializing infile, outfile, opt, byte, msg 1 and 2, and creates bit matrix g and h transpose
    struct stat statbuf;
    FILE *outfile = stdout;
    int opt = 0;
    int byte1;
    int byte2;
    bool verbose = false;
    uint8_t msg1;
    uint8_t msg2;
    uint8_t code;
    BitMatrix *G = bm_create(4, 8);
    BitMatrix *Ht = bm_create(8, 4);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code decoder.\n\n");
            printf("USAGE\n");
            printf("   ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
            printf("   -v             Print statistics of decoding to stderr.\n");
            printf("   -i infile      Input data to encode.\n");
            printf("   -o outfile     Output of encoded data.\n");
            return 0;
        case 'i': // opens infile specified
            infile = fopen(optarg, "r");
            if (infile == NULL || errno == EINVAL) {
                printf("Error: failed to open infile.\n");
                return 0;
            }
            break;
        case 'o': // opens outfile specified
            outfile = fopen(optarg, "w");
            if (outfile == NULL || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                fclose(outfile);
                return 0;
            }
            break;
        case 'v': // prints out stats
            verbose = true;
            fstat(fileno(infile), &statbuf);
            fchmod(fileno(outfile), statbuf.st_mode);
            break;
        default: // if incorrect input
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code decoder.\n\n");
            printf("USAGE\n");
            printf("   ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
            printf("   -v             Print statistics of decoding to stderr.\n");
            printf("   -i infile      Input data to encode.\n");
            printf("   -o outfile     Output of encoded data.\n");
            return 0;
        }
    }
    for (uint32_t i = 0; i < 4;
         i++) { // sets bit matrix for generator matrix and H transpose matrix
        bm_set_bit(G, i,
            i); // sets bit for generator matrix which only has 1's across the diagonal for the first 4 columns
        for (uint32_t j = 0; j < 4; j++) {
            if (i != j) {
                bm_set_bit(Ht, i,
                    j); // for the first 4 by 4 part of the h transpose matrix, sets all bits except for the diagonal
            }
        }
    }
    for (uint32_t i = 0; i < 4; i++) { // for all rows
        for (uint32_t j = 4; j < 8; j++) { // for columns 5-8
            if ((j - i) != 4) { // j - i reveals whether specified bit is on diagonal
                bm_set_bit(G, i, j); // sets bit for everything except diagonal
            }
        }
    }
    for (uint32_t i = 4; i < 8; i++) { // for rows 5 - 8
        for (uint32_t j = 0; j < 4; j++) { // for all columns
            if ((i - j) == 4) { // i - j revealse whether bit is on diagonal
                bm_set_bit(Ht, i, j); // sets bit if not on diagonal
            }
        }
    }
    while (fgetc(infile) != EOF) { // until byte reaches end of file
        byte1 = fgetc(infile); // gets first byte and second byte
        byte2 = fgetc(infile);
        ham_decode(Ht, byte1, &msg1); // decodes both bytes into msg1 and 2
        ham_decode(Ht, byte2, &msg2);
        code = pack_byte(msg1, msg2); // packs both msgs together
        fputc(code, outfile); // puts code into outfile
    }
    if (verbose) {
        printf("Total bytes processed: %ld\n",
            statbuf
                .st_size); // prints out stats (i.e bytes processed, uncorrected errors, corrected errors, error rate
        printf("Uncorrected errors: %d\n", uc);
        printf("Corrected errors: %d\n", crr);
        printf("Error rate: %ld\n", (uc / (statbuf.st_size)));
    }
    bm_delete(
        &G); // free memory allocated for generator matrix, h transpose matrix, and closes infile and outfile
    bm_delete(&Ht);
    fclose(infile);
    fclose(outfile);
    return 0;
}
