#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    int opt = 0;
    int infile = 0;
    int outfile = 1;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  A Huffman decoder.\n");
            printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("  ./decode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to decompress.\n");
            printf("  -o outfile     Output of decompressed data.\n");
            return 0;
        case 'i': // opens infile specified
            infile = open(optarg, O_RDONLY);
            if (infile == -1 || errno == EINVAL) {
                printf("Error: failed to open infile.\n");
                close(infile);
                return 0;
            }
            break;
        case 'o': // opens outfile specified
            outfile = open(optarg, O_WRONLY);
            if (outfile == -1 || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                close(outfile);
                return 0;
            }
            break;
        case 'v': // prints out stats
            verbose = true;
            break;
        default: // if incorrect input
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("  A Huffman decoder.\n");
            printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("  ./decode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to decompress.\n");
            printf("  -o outfile     Output of decompressed data.\n");
        }
    }
    Header h = { 0 }; // creates a header to read info into
    read_bytes(infile, (uint8_t *) &h, sizeof(Header)); // gets data for header
    if (h.magic != MAGIC) { // checks if file is the same that was encoded
        printf("Error: unable to read header.\n");
        return 0;
    }
    fchmod(outfile, h.permissions); // sets permission of outfile to infile
    uint8_t treedump[h.tree_size]; // creates a treedump array of tree_size
    uint8_t buff[h.tree_size]; // creates a buffer array of tree size
    int bytes = 0;
    bytes = read_bytes(infile, buff, h.tree_size); // gets info to rebuild tree later on
    for (int i = 0; i < bytes; i++) {
        treedump[i] = buff[i]; // sets character in buff into treedump
    }
    Node *root = rebuild_tree(h.tree_size, treedump); // creates tree again
    Node *curr = root;
    uint8_t bit = 0;
    uint64_t fsc = 0;
    while (read_bit(infile, &bit)) { // reads in bits to decode
        if (bit == 0) { // if bit is 0 then move left on the tree
            curr = curr->left;
        } else { // if bit is 1 move right on the tree
            curr = curr->right;
        }
        // if current node is a leaf then print that character to outfile
        if (((curr->left) == NULL) && ((curr->right) == NULL)) {
            uint8_t cha[1];
            cha[0] = curr->symbol;
            write_bytes(outfile, cha, 1);
            fsc += 1;
            curr = root;
        }
        // if outfile size is = to original infile size then brea,k
        if (fsc == h.file_size) {
            break;
        }
    }
    delete_tree(&root); // free memory allocated for root, current
    //delete_tree(&curr);
    close(infile); // close infile and outfile
    close(outfile);
    return 0;
}
