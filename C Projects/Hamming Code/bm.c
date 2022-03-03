#include "bm.h"

#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

BitMatrix *bm_create(uint32_t rows,
    uint32_t
        cols) { // allocates memory for matrix and allocates memory for vector. Also sets rows and cols in matrix
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->vector = bv_create((rows * cols));
    return m;
}

void bm_delete(BitMatrix **m) { // frees all allocated memory
    bv_delete(&(*m)->vector);
    free(*m);
    *m = NULL;
}

uint32_t bm_rows(BitMatrix *m) { // returns rows
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) { // return cols
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) { // sets a bit from r and c position
    bv_set_bit(m->vector, ((r * (m->cols)) + c));
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) { // clears a bit from r and c position
    bv_clr_bit(m->vector, ((r * (m->cols)) + c));
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) { // return bit from matrix
    return bv_get_bit(m->vector, ((r * (m->cols)) + c));
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *a = bm_create(1, length); // returns a matrix 1 rows and length cols
    for (uint32_t i = 0; i < length; i++) { // loops thorugh until length
        if (byte & (1 << i)) { // if ith bit is 1 then set a vector to 1 else clear it
            bm_set_bit(a, 0, i);
        } else {
            bm_clr_bit(a, 0, i);
        }
    }
    return a;
}

uint8_t bm_to_data(BitMatrix *m) { // returns first 8 bits of matrix
    uint8_t val = 0;
    for (int i = 0; i < 8; i++) { // loops through first 8
        val |= (bm_get_bit(m, 0, i)
                << i); // sets val = the bit taken from 0th row i col but because get bit return bit in left most position, I left shift it to actual position
    }
    return val;
}

BitMatrix *bm_multiply(BitMatrix *A,
    BitMatrix *
        B) { // multiplies two matrices (i.e a (mxn) and b (nxp)) and return a new matrix (i.e c (mxp)) that follows matrix multiplication rules
    if (A->cols == B->rows) { // checks if a cols and b rows are the same
        BitMatrix *c = bm_create(A->rows, B->cols); // creates a new matrix
        for (uint32_t i = 0; i < A->rows; i++) { // loops through a rows
            for (uint32_t j = 0; j < B->cols; j++) { // loops through b cols
                uint8_t bit = 0; // initalizes bit
                for (uint32_t k = 0; k < A->cols; k++) { // loops through a cols or b rows
                    bit ^= (bm_get_bit(A, i, k)
                            & bm_get_bit(B, k, j)); // XOR's the AND of the two bits of a and b
                }
                if (bit == 1) { // if bit = 1, then it sets the bit or else it clears it
                    bm_set_bit(c, i, j);
                } else {
                    bm_clr_bit(c, i, j);
                }
            }
        }
        return c; // return new matrix
    }
    return 0;
}

void bm_print(BitMatrix *m) { // print matrix
    bv_print(m->vector);
    return;
}
