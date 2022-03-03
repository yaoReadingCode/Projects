#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]) {
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 4);
	addEdge(G, 2, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 6);
	addEdge(G, 3, 5);
	addEdge(G, 3, 6);
	addEdge(G, 4, 5);
	printf("There are %d vertices and %d edges\n", getOrder(G), getSize(G));
	printGraph(stdout, G);
	BFS(G, 4);
	List L = newList();
	getPath(L, G, 6);
	int x = getDist(G, 6);
	printf("The Distance between 4 and 6 is %d\n", x);
	printf("The shortest path between 4 and 6 is : ");
	printList(stdout, L);
	makeNull(G);
	printf("Graph now has no edges because makeNull deleted them and thus getSize(G) is now %d\n", getSize(G));
	printf("This program has now tested all functions from Graph.c. Either explicity, or through a function that uses other functions. Good Day\n");
	return 0;
}
