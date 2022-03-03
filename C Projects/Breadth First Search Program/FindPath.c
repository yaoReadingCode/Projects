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
//	for (int i = 0; i < c; i++) {
//		int m = fscanf(in, "%d" "%d", &x, &y);
//		if (m != 2) {
//			printf("Error: did not read in correct numbers\n");
//		}
//		addEdge(G, x, y);
//	}
	while ((m = fscanf(in, "%d" "%d\n", &x, &y)) != EOF) {
		if (x == 0 && y == 0) {
			break;
		}
		//printf("%d %d\n", x, y);
		addEdge(G, x, y);
	}
	printGraph(out, G);
	//fprintf(stdout, "\n");
	List L = newList();
	while ((m = fscanf(in, "%d" "%d\n", &x, &y)) != EOF) {
                if (x == 0 && y == 0) {
                        break;
                }
		BFS(G, x);
		getPath(L, G, y);
		int z = getDist(G, y);
		if (z == -6) {
			fprintf(out, "\nThe distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists\n", x, y);
		}
		else {
			fprintf(out, "\nThe distance from %d to %d is %d\n", x, y, z);
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			printList(out, L);
		}
		clear(L);
	}
//	printList(stdout, L);
//	free(*strings);
//	*strings=NULL;
	freeList(&L);
	freeGraph(&G);
	fclose(in);
	fclose(out);
	return(0);
}
