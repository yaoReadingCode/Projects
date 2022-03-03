#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(
    void) { // creates a "path" which keeps track of the length of the path and also acts as a wrapper for the stack
    Path *p = (Path *) malloc(sizeof(Path)); // allocates size for path
    p->vertices = stack_create(VERTICES); // creates a stack based on max number of vertices, 26
    p->length = 0; // initalizes p->length to 0
    return p;
}

void path_delete(Path **p) {
    stack_delete((&(*p)->vertices)); // frees stack, pointer, and sets pointer to NULL
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) { // pushes a vetice onto stack
    if (!stack_empty(
            p->vertices)) { // if stack is not empty, the adds the weight between current vertice and previous vertice onto length because you travel from previous vertice to current
        uint32_t w = 0;
        stack_peek(p->vertices, &w);
        p->length += graph_edge_weight(G, w, v);
    }
    uint32_t t;
    stack_push(p->vertices, v); // pushes vertice onto stack
    stack_peek(p->vertices,
        &t); // checks to make sure vertice has been pushed onto stack, if so true, else false
    if (v == t) {
        return true;
    } else {
        return false;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) { // pops a vertice onto stack
    stack_pop(p->vertices, v); // pops vertice
    uint32_t w = 0; // intializes w
    stack_peek(p->vertices, &w); // looks at previous vertice
    p->length = (p->length)
                - graph_edge_weight(
                    G, w, *v); // subtracts weight between previous vertice and current from length
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); // returns size of stack
}

uint32_t path_length(Path *p) { // return length
    return p->length;
}

void path_copy(Path *dst, Path *src) { // copies all stack from source onto distance
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length; // copies length from source onto length
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) { // prints out path
    stack_print(p->vertices, outfile, cities);
    return;
}
