#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices,
    bool
        undirected) { // allocates size for a graph, initalizes vertices and matrix, and sets vertices and undirected to inputed values
    Graph *G = (Graph *) malloc(sizeof(Graph));
    for (uint32_t i = 0; i < VERTICES; i++) {
        G->visited[i] = false;
        for (uint32_t j = 0; j < VERTICES; j++) {
            G->matrix[i][j] = 0;
        }
    }
    G->undirected = undirected;
    G->vertices = vertices;
    return G;
}

void graph_delete(Graph **G) { // free memory allocated for graph
    free(*G);
    *G = NULL;
}

uint32_t graph_vertices(Graph *G) { // return number of vertices
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j,
    uint32_t
        k) { // adds weight between two vertices. If undirected, sets ij and ji to same weight, otherwise just ij
    if (i < VERTICES && j < VERTICES && i >= 0 && j >= 0) { // checks if vertices are inbounds
        if (G->undirected) {
            G->matrix[i][j] = k;
            G->matrix[j][i] = k;
            return true;
        } else {
            G->matrix[i][j] = k;
            return true;
        }
    } else {
        return false;
    }
}

bool graph_has_edge(Graph *G, uint32_t i,
    uint32_t
        j) { // checks if weight between two vertices ij is greater than 0; if > 0 then return true, else falsee
    if (i >= 0 && i < VERTICES && j >= 0 && j < VERTICES) {
        if (G->matrix[i][j]) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(
    Graph *G, uint32_t i, uint32_t j) { // returns weight between two inbound vertices
    if (i >= 0 && i < VERTICES && j >= 0 && j < VERTICES && graph_has_edge(G, i, j)) {
        return G->matrix[i][j];
    } else {
        return 0;
    }
}

bool graph_visited(
    Graph *G, uint32_t v) { // returns whether a vertice has been visited (true or false)
    if (v >= 0 && v < VERTICES) {
        return G->visited[v];
    } else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) { // marks a vertice as visited
    if (v >= 0 && v < VERTICES) {
        G->visited[v] = true;
        return;
    } else {
        return;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) { // marks a vertice as unvisited
    if (v >= 0 && v < VERTICES) {
        G->visited[v] = false;
        return;
    } else {
        return;
    }
}

void graph_print(Graph *G) { // prints graph
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%" PRIu32, G->matrix[i][j]);
        }
    }
    return;
}
