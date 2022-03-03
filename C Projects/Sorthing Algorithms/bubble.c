#include "bubble.h"

#include "stat.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped; // initalize array
    uint32_t len = n; // n = size of array
    do {
        swapped = false;
        for (uint32_t i = 1; i < len; i += 1) {
            if (greater_than(A[i - 1], A[i])) { //compares two elements of array
                swap(&A[i - 1], &A[i]); // swaps the two of them
                swapped = true;
            }
        }
        len -= 1;
    } while (swapped);
    return;
}
