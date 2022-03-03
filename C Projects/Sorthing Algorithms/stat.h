#ifndef __STAT_H__
#define __STAT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern uint32_t compares; // counts the # of comparisons

extern uint32_t moves; // counts the # of moves

bool less_than(int64_t x, int64_t y);

bool greater_than(int64_t x, int64_t y);

void swap(uint32_t *x, uint32_t *y);

void move(uint32_t *x, uint32_t *y);

#endif
