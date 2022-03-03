#include "quick.h"

#include "queue.h"
#include "stack.h"
#include "stat.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    int64_t pivot = A[lo + ((hi - lo) / 2)]; // creates a pivot point
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i += 1;
        while (less_than(A[i], pivot)) { // compares two elements
            i += 1;
        }
        j -= 1;
        while (greater_than(A[j], pivot)) { // compares two elements
            j -= 1;
        }
        if (i < j) {
            swap(&A[i], &A[j]); // swaps two elements
        }
    }
    return j; // returns j
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = (n - 1);
    Stack *s = stack_create(n); // creates a stack
    stack_push(s, lo); // pushes lo then hi
    stack_push(s, hi);
    if (maxs < stack_size(s)) {
        maxs = stack_size(s);
    }
    while (stack_size(s) != 0) {
        stack_pop(s, &hi); // pops elements and sets hi to it
        stack_pop(s, &lo); // pops element and sets lo to it
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo); // pushs lo then p
            stack_push(s, p);
        }
        //printf("stack size is %u and max is %ld\n", stack_size(s), maxs);
        if (maxs < stack_size(s)) {
            printf("%ld is max\n", maxs);
            maxs = stack_size(s);
        }
        if (hi > (p + 1)) {
            stack_push(s, (p + 1)); // pushes (p+1) then hi
            stack_push(s, hi);
        }
        if (maxs < stack_size(s)) {
            maxs = stack_size(s);
        }
    }
    stack_delete(&s); // deletes stack to prevent leaks
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = (n - 1);
    Queue *q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    if (maxq < queue_size(q)) {
        maxq = queue_size(q);
    }
    while (queue_size(q) != 0) {
        dequeue(q, &lo);
        dequeue(q, &hi);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (maxq < queue_size(q)) {
            maxq = queue_size(q);
        }
        if (hi > (p + 1)) {
            enqueue(q, (p + 1));
            enqueue(q, hi);
        }
        if (maxq < queue_size(q)) {
            maxq = queue_size(q);
        }
    }
    queue_delete(&q);
}
