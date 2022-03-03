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

void dump_tree(int outfile, Node *root) {
    if ((root->left == NULL) && (root->right == NULL)) { // checks if root is a leaf node
        uint8_t bufff[2]; // creates an array to hold letters
        bufff[0] = 'L'; // sets first byte to L which stands for leaf
        bufff[1] = (root->symbol); // sets second byte to symbol
        write_bytes(outfile, bufff, 2); // write array to outfile
    } else {
        dump_tree(outfile, (root->left)); // recursively calls dump tree if not a leaf node
        dump_tree(outfile, (root->right));
        uint8_t bufff[1]; // creates a buffer of 1 to hold letter I
        bufff[0] = 'I'; // sets first byte to I which stands for inner node
        write_bytes(outfile, bufff, 1); // write it to outfile
    }
}

int main(int argc, char **argv) {
    int opt = 0; // initializes opt, stat buffer, infile, outfile and verbose
    struct stat buffer;
    int infile = 0;
    int outfile = 1;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  A Huffman encoder.\n\n");
            printf("  Compresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to compress.\n");
            printf("  -o outfile     Output of compressed data.\n");
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
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
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
            printf("  A Huffman encoder.\n\n");
            printf("  Compresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to compress.\n");
            printf("  -o outfile     Output of compressed data.\n");
        }
    }
    fstat(infile, &buffer); // gets stats of infile into buffer
    struct stat bufout;
    fstat(infile, &bufout);
    fchmod(outfile, buffer.st_mode); // sets permissions of outfile to infile
    uint8_t buff[BLOCK] = { 0 }; // creates a buffer of size BLOCK 4096
    uint64_t hist[ALPHABET] = { 0 };
    int bytes = 0; // initalizes bytes, total, and size
    int total = 0;
    int size = 0;
    Code table[ALPHABET] = { 0 }; // creates a table which is a sort of stack of size ALPHABET
    while ((bytes = read(infile, buff, BLOCK)) > 0) { // reads infile to get all characters in it
        for (int i = 0; i < bytes; i++) { // for every symbol in buffer, add 1 frequency to hist
            hist[buff[i]] += 1;
        }
        total += bytes; // total bytes read
    }
    for (int i = 0; i < ALPHABET; i++) { // for everysymbol with frequency > 1, add 1 to size
        if (hist[i] > 0) {
            size += 1;
        }
    }
    hist[0] += 1; // add 1 to freq. for 0 and 255 and add 2 to size
    hist[255] += 1;
    size = size + 2;
    Node *n = build_tree(hist); // builds tree and joins together all nodes to get root
    build_codes(n, table); // builds codes for each symbol that will be put into outfile
    Header h = { 0 }; // creates and intializes header
    h.magic = MAGIC; // sets header to magic number
    h.permissions = buffer.st_mode; // sets header permissions to infile permissions
    h.tree_size = ((3 * size) - 1); // sets header tree size
    h.file_size = buffer.st_size; // sets file size infile file size
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header)); // writes header to outfile
    uint8_t bu[BLOCK]; // creates a buffer array for to read infile into again
    dump_tree(outfile, n); // writes tree information into outfile
    lseek(infile, 0, SEEK_SET); // sets read offset to beginning
    while ((bytes = read(infile, bu, BLOCK))) { // reads in characters
        for (int i = 0; i < bytes; i++) {
            // for each character, gets much smaller in size code and writes to outfile
            write_code(outfile, &table[bu[i]]);
        }
        flush_codes(outfile);
    }
    uint64_t cfs = total; // compressed filed size
    uint64_t ss = (100 * (1 - (cfs / h.file_size))); // saved space
    if (verbose) { // prints stats if verbose is true
        fprintf(stderr,
            "Uncompressed file size: %" PRIu64 "\nCompressed file size: %" PRIu64
            "\nSpace saving: %" PRIu64 "\n",
            h.file_size, cfs, ss);
    }
    // deletes tree allocated memory, closes infile and outfile
    delete_tree(&n);
    close(infile);
    close(outfile);
    return 0;
}
