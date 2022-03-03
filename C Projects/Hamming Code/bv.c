#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1,
        sizeof(
            BitVector)); // allocates memory for bitvector v, initalizes length, and allocates memory for v->vector
    v->length = length;
    int val = length % 8 == 0 ? length / 8 : (length / 8 + 1);
    v->vector = (uint8_t *) calloc(val, sizeof(uint8_t));
    return v;
}

void bv_delete(BitVector **v) { // frees all allocated memory and pointers
    free((*v)->vector);
    free(*v);
    *v = NULL;
}

uint32_t bv_length(BitVector *v) { // return length
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) { // sets a bit in a vector to 1
    v->vector[i / 8] |= (1 << (i % 8));
    return;
}

void bv_clr_bit(BitVector *v, uint32_t i) { // sets a bit in a vector to 0
    v->vector[i / 8] &= ~(1 << (i % 8));
    return;
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) { // inclusive ORs a bit in a vector
    bit = v->vector[i / 8] ^ (1 << (i % 8));
    return;
}

uint8_t bv_get_bit(BitVector *v,
    uint32_t
        i) { // returns a bit from a specified location that is shifted it to the Least value bit
    return ((v->vector[i / 8] & (1 << (i % 8))) >> (i % 8));
}

void bv_print(BitVector *v) { // prints vector
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%" PRIu32, v->vector[i]);
    }
    printf("\n");
    return;
}
