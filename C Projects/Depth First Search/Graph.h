#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>
#include "List.h"

#define NIL     0
#define INF     -6
#define UNDEF	-7


// Exported Type

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List L);

/*** Other operations ***/

void printGraph(FILE* out, Graph G);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

#endif

