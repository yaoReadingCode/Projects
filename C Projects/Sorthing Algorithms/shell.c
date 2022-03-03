#include "shell.h"

#include "gaps.h"
#include "stat.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t g = 0; g < GAPS; g += 1) {
        for (uint32_t i = gaps[g]; i < n;
             i += 1) { // if the gap is larger than the size of the array, it skips it
            uint32_t j = i;
            uint32_t temp = 0;
            move(&temp, &A[i]); // moves array elements into temp
            while (j >= gaps[g] && less_than(temp, A[j - gaps[g]])) {
                move(&A[j], &A[j - gaps[g]]); // moves array elements into another one
                j -= gaps[g];
            }
            move(&A[j], &temp); // moves array element temp into A[j]
        }
    }
}
