#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"
#include<string.h>

int main(int argc, char * argv[]) {
	FILE *in, *out;
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
        if (out == NULL) {
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
	int c;
	int x;
	int y;
	int m;
	fscanf(in, "%d", &c);
	Graph G = newGraph(c);
	while ((m = fscanf(in, "%d" "%d\n", &x, &y)) != EOF) {
		if (x == 0 && y == 0) {
			break;
		}
		//printf("%d %d\n", x, y);
		addArc(G, x, y);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	List S = newList();
	for(int i=1; i<(c+1); i++) append(S, i);
	DFS(G, S);
	Graph NG = transpose(G);
	DFS(NG, S);
	moveBack(S);
	int count = 0;
	for (int i = 0; i<length(S); i++) {
		if (getParent(NG, get(S)) == 0) {
			count++;
		}
		movePrev(S);
	}
	fprintf(out, "\nG contains %d strongly connected components:\n", count);
	List SCC = newList();
	moveBack(S);
	count = 1;
	for (int i = 0; i < length(S); i++) {
		prepend(SCC, get(S));
                if (getParent(NG, get(S)) == 0) {
			fprintf(out, "Component %d: ", count);
			printList(out, SCC);
			clear(SCC);
			count++;
                }
		movePrev(S);
        }
	freeList(&S);
	freeList(&SCC);
	freeGraph(&NG);
	freeGraph(&G);
	fclose(in);
	fclose(out);
	return(0);
}

