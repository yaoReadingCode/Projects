#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

Stack *stack_create(uint32_t
        capacity) { //Creates a stack. Provided by the teacher. Had a version of this written myself but did not include the if statements. Felt that the professors code was smarter.
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = 0;
    s->capacity = capacity;
    s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
    return s;
}

void stack_delete(Stack **
        s) { // provided by teacher. Had a version of this written myself but did not include the if statements. Felt that the professors code was smarter.
    free((*s)->items);
    free(*s);
    *s = NULL;
    return;
}

bool stack_empty(Stack *s) { // checks if stack is empty. Only used in this file.
    return s->top == 0;
}

bool stack_full(Stack *s) { // checks if stack is full. Only used in this file.
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) { // returns size of stack.
    uint32_t n = s->top;
    return n;
}

bool stack_push(Stack *s,
    uint32_t
        x) { // pushes values on stack. If stack is full prior to pushing item, it returns false.
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s,
    uint32_t
        *x) { // pops values on stack. If stack is empty prior to popping item, it returns false.
    if (stack_empty(s)) {
        return false;
    }
    s->top = (s->top) - 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s,
    uint32_t *
        x) { // return element from below top pointer otherwise known as element at the top of the stack
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[(s->top) - 1];
        return true;
    }
}

void stack_copy(Stack *dst,
    Stack *
        src) { // copies all items from source stack to destination stack, then copies where the source top point to the destination top point
    for (uint32_t i = 0; i < (src->top); i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top;
    return;
}

void stack_print(
    Stack *s, FILE *outfile, char *cities[]) { // provided by Eugene. Print contents of stack.
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
