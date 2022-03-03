#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "List.h"
#include "Graph.h"

#define WHITE	-2
#define GREY	-3
#define BLACK	-4


// Exported Type

typedef struct GraphObj {
	List *vertices;
	int *color;
	int *parent;
	int *discover_time;
	int order;
	int size;
	int *finish_time;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->vertices = calloc((n+1), sizeof(List));
	for (int i = 0; i < (n+1); i++) {
		G->vertices[i] = newList();
	}
	G->color = (int *) calloc((n+1), sizeof(int));
	G->parent = (int *) calloc((n+1), sizeof(int));
	G->discover_time = (int *) calloc((n+1), sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->finish_time = (int *) calloc((n+1), sizeof(int));
	for (int i = 1; i < (n+1); i++) {
                G->discover_time[i] = UNDEF;
                G->finish_time[i] = UNDEF;
                G->parent[i] = NIL;
        }
	return G;
}

void freeGraph(Graph* pG) {
	free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover_time);
	free((*pG)->finish_time);
	if(pG!=NULL && *pG!=NULL) {
                for (int i = 0; i<(((*pG)->order)+1); i++) {
                        freeList(&(*pG)->vertices[i]);
                }
                free(*pG);
                *pG = NULL;
        }
}


/*** Access functions ***/

int getOrder(Graph G) {
	return G->order;
}

int getSize(Graph G) {
	return G->size;
}

int getParent(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: u was not within bounds\n");
                exit(EXIT_FAILURE);
	}
	else {
		return G->parent[u];
	}
}

int getDiscover(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
                printf("Graph Error: u was not within bounds\n");
                exit(EXIT_FAILURE);
        }
	else {
		return G->discover_time[u];
	}
}

int getFinish(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
                printf("Graph Error: u was not within bounds\n");
                exit(EXIT_FAILURE);
        }
	else {
		return G->finish_time[u];
	}
}



/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v) {
	if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
		int a = isEmpty(G->vertices[u]);
		int b = isEmpty(G->vertices[v]); 
		if (a) {
			append(G->vertices[u], v);
		}
		else {
			moveFront(G->vertices[u]);
			while (get(G->vertices[u]) < v) {
				moveNext(G->vertices[u]);
				if (index(G->vertices[u]) == -1) {
					break;
				}
			}
			if (index(G->vertices[u]) == -1) {
				append(G->vertices[u], v);
			}
			else {
				insertBefore(G->vertices[u], v);
			}
		}
		if (b){
			append(G->vertices[v], u);
		}
		else {
			moveFront(G->vertices[v]);
                        while (get(G->vertices[v]) < u) {
                                 moveNext(G->vertices[v]);
				 if (index(G->vertices[v]) == -1) {
                                         break;
                                 }
                         }       
                         if (index(G->vertices[v]) == -1) {
                                 append(G->vertices[v], u);
                         }       
                         else {  
                                 insertBefore(G->vertices[v], u);
                         } 
		}
	}
	G->size+=1;
		
}

void addArc(Graph G, int u, int v) {
	if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
                int a = isEmpty(G->vertices[u]);
                if (a) {
                        append(G->vertices[u], v);
                }
                else {
                        moveFront(G->vertices[u]);
                        while (get(G->vertices[u]) < v) {
                                moveNext(G->vertices[u]);
                                if (index(G->vertices[u]) == -1) {
                                        break;
                                }
                        }
                        if (index(G->vertices[u]) == -1) {
                                append(G->vertices[u], v);
                        }
                        else {
                                insertBefore(G->vertices[u], v);
                        }
                }
	}
	G->size+=1;
}

int Visit(Graph G, int x, List L, int time) {
	G->discover_time[x] = ++time;
	G->color[x] = GREY;
	if (length(G->vertices[x]) != 0) {
		moveFront(G->vertices[x]);
		for (int i = 0; i < length(G->vertices[x]); i++) {
			int y = get(G->vertices[x]);
                	if (G->color[y] == WHITE) {
                        	G->parent[y] = x;
				time = Visit(G, y, L, time);
			}
			moveNext(G->vertices[x]);
		}
	 }
	 G->color[x] = BLACK;
         G->finish_time[x] = ++time;
         insertAfter(L, x);
	 return time;
}

void DFS(Graph G, List L) {
	for (int i = 1; i < ((G->order)+1); i++) {
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover_time[i] = UNDEF;
		G->finish_time[i] = UNDEF;
	}
	int time = 0;
	moveBack(L);
	int a;
	for (int j = 0; j < G->order; j++) {
		a = front(L);
		if (G->color[a] == WHITE) {
			time = Visit(G, a, L, time);
		}
		deleteFront(L);
	}
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i < ((G->order) + 1); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->vertices[i]);
	}
}

Graph transpose(Graph G) {
	int e;
	int s = getOrder(G);
	Graph T = newGraph(s);
	for (int i = 1; i < ((G->order) + 1); i++) {
		moveFront(G->vertices[i]);
		for (int j = 0; j < (length(G->vertices[i])); j++) {
			e = get(G->vertices[i]);
			addArc(T, e, i);
			moveNext(G->vertices[i]);
		}
	}
	return T;
}

Graph copyGraph(Graph G) {
	Graph N = newGraph(G->order);
	for (int i = 1; i < (getOrder(G) + 1); i++) {
		N->vertices[i] = copyList(G->vertices[i]);
		N->parent[i] = G->parent[i];
		N->color[i] = G->color[i];
		N->discover_time[i] = G->discover_time[i];
		N->finish_time[i] = G->finish_time[i];
	}
	N->order = getOrder(G);
	N->size = getSize(G);
	N->source = G->source;
	return N;
}

