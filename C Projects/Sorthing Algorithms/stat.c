#include "stat.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool less_than(int64_t x, int64_t y) {
    compares += 1; // compare counter
    if (x < y) {
        return true;
    } else {
        return false;
    }
}

bool greater_than(int64_t x, int64_t y) {
    compares += 1; // compare counter
    if (x > y) {
        return true;
    } else {
        return false;
    }
}

void swap(uint32_t *x, uint32_t *y) {
    moves += 3; // moves counter +3 because it involes three moves
    uint32_t temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void move(uint32_t *x, uint32_t *y) {
    moves += 1; // moves counter
    x = y;
    return;
}
