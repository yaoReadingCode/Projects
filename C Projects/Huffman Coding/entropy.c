#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BYTE    256
#define KBYTE   1024
#define OPTIONS "h"

static uint64_t number = 0, count[BYTE] = { 0 };

static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A entropy measuring program.\n"
        "\n"
        "USAGE\n"
        "  %s < [input (reads from stdin)]\n"
        "\n"
        "OPTIONS\n"
        "  -h               Program usage and help.\n",
        exec);
}

// Count the number of occurences of each byte value 0..255
static void tally(int file) {
    int length;
    uint8_t buffer[KBYTE] = { 0 };
    while ((length = read(file, buffer, KBYTE)) > 0) {
        number += length;
        for (int i = 0; i < length; i += 1) {
            count[buffer[i]] += 1;
        }
    }
    return;
}

//  ∞
// -∑ Pr(x ) log (x )
// i=1    i     2  i
static double entropy(int file) {
    tally(file);
    double sum = 0.0;
    for (int i = 0; i < BYTE; i += 1) {
        double p = (double) count[i] / (double) number;
        if (p > 0) {
            sum += p * log2(p);
        }
    }
    return -sum;
}

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    printf("%lf\n", entropy(STDIN_FILENO));
    return 0;
}
