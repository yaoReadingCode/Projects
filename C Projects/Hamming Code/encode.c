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
#include <unistd.h>

#define OPTIONS "hi:o:"

uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

int main(int argc, char **argv) {
    FILE *infile
        = stdin; // intializing infile, outfile, opt, byte, msg 1 and 2, and creates bit matrix g and h transpose
    FILE *outfile = stdout;
    int opt = 0;
    int byte;
    uint8_t msg1;
    uint8_t msg2;
    BitMatrix *G = bm_create(4, 8);
    BitMatrix *Ht = bm_create(8, 4);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code generator.\n\n");
            printf("USAGE\n");
            printf("   ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
            printf("   -i infile      Input data to encode.\n");
            printf("   -o outfile     Output of encoded data.\n");
            return 0;
        case 'i': // opens infile specified
            infile = fopen(optarg, "rb");
            if (infile == NULL || errno == EINVAL) {
                printf("Error: failed to open infile.\n");
                return 0;
            }
            break;
        case 'o': // opens outfile specified
            outfile = fopen(optarg, "wb");
            if (outfile == NULL || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                fclose(outfile);
                return 0;
            }
            break;
        default: // if incorrect option inputed, stderr
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code generator.\n\n");
            printf("USAGE\n");
            printf("   ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
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
    while ((byte = fgetc(infile)) != EOF) { // until byte reaches end of file
        msg1 = lower_nibble(byte); // sets msg1 to lower part of byte
        msg2 = upper_nibble(byte); // sets msg2 to upper part of byte
        uint8_t code1 = ham_encode(G, msg1); // encodes msg1
        fputc(code1, outfile); // puts encoded msg into outfile
        uint8_t code2 = ham_encode(G, msg2); // encodes msg2
        fputc(code2, outfile); // puts encoded msg into outfile
    }
    bm_delete(&G); // frees generator matrix
    bm_delete(&Ht); // frees h transpose matrix
    fclose(infile); // close infile and outfile
    fclose(outfile);
    return 0;
}
