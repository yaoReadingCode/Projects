#include<stdlib.h>
#include<stdbool.h>
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
	int *distance;
	int order;
	int size;
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
	G->distance = (int *) calloc((n+1), sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

void freeGraph(Graph* pG) {
	free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
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

int getSource(Graph G) {
	return G->source;
}

int getParent(Graph G, int u) {
	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: u was not within bounds\n");
                exit(EXIT_FAILURE);
	}

	if (G->source == NIL) {
		return NIL;
	}
	else {
		return G->parent[u];
	}
}

int getDist(Graph G, int u) {
	if (G->source == NIL) {
		return INF;
	}
	else {
		return G->distance[u];
	}
}

void getPath(List L, Graph G, int u) {
	if ( getSource(G)==NIL ) {
		printf("Path Error: DFS was not run before\n");
                exit(EXIT_FAILURE);
	}
	if (u == getSource(G)) {
		append(L, u);
	}
	else if (G->parent[u] == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}



/*** Manipulation procedures ***/

void makeNull(Graph G) {
	for (int i = 1; i<((G->order)+1); i++) {
                        clear(G->vertices[i]);
			G->size = 0;
	}
}

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

void BFS(Graph G, int s) {
	G->source = s;
	//printf("hello");
	for (int i = 1; i < ((G->order)+1); i++) {
		if (i != s) {
			G->color[i] = WHITE;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
	}
	G->color[s] = GREY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	//printf("hello");
	append(L, s);
	int y;
	//printList(stdout, L);
	while (length(L) != 0) {
		int f = front(L);
		deleteFront(L);
		moveFront(G->vertices[f]);
		for (int j = 0; j < (length(G->vertices[f])); j++) {
       			y = get(G->vertices[f]);
			if (G->color[y] == WHITE) {
				G->color[y] = GREY;
				G->distance[y] = (G->distance[f]) + 1;
				G->parent[y] = f;
				append(L, y);
			}
			moveNext(G->vertices[f]);
		}
		G->color[f] = BLACK;
	}
	freeList(&L);
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i < ((G->order) + 1); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->vertices[i]);
	}
}
