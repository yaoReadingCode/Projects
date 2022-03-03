#include "code.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Code code_init(void) {
    Code c; // declares code c
    c.top = 0; // sets top to 0
    return c;
}

uint32_t code_size(Code *c) {
    return c->top; // returns size
}

bool code_empty(Code *c) {
    return (c->top == 0); // returns true if code is empty
}

bool code_full(Code *c) {
    return (c->top == ALPHABET); // returns true if code is full
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) { // if code is full, return false
        return false;
    }
    if (bit == 1) {
        c->bits[(c->top) / 8] |= (1 << ((c->top) % 8)); // sets bit at top of stack
    } else {
        c->bits[(c->top) / 8] &= ~(1 << ((c->top) % 8)); // clears bit at top of stack
    }
    c->top += 1; // increases top by 1
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) { // if code is empty, return false
        return false;
    }
    c->top = c->top - 1; // decreases top by 1
    c->bits[(c->top) / 8] &= ~(1 << ((c->top) % 8));
    *bit = ((c->bits[(c->top) / 8] & (1 << ((c->top) % 8))) >> ((c->top) % 8));
    return true;
}

void code_print(Code *c) { // prints out all bits up to top
    for (uint32_t i = 0; i < c->top; i++) {
        printf("Bit is ");
        printf("%" PRIu8, c->bits[i]);
        printf("\n");
    }
    return;
}
