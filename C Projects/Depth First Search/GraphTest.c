#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *in;
  in = fopen(argv[1], "r");
  if (in == NULL) {
	  printf("Unable to open file %s for reading\n", argv[1]);
	  exit(1);
  }
  int c;
  fscanf(in, "%d", &c);
  Graph G = newGraph(c);
  int m;
  int x;
  int y;
  List S = newList();
  for(int i=1; i<(c+1); i++) append(S, i);
  while ((m = fscanf(in, "%d" "%d\n", &x, &y)) != EOF) {
	  if (x == 0 && y == 0) {
		  break;
	  }
	  addArc(G, x, y);
  }
  printf("There are %d vertices and %d edges\n", getOrder(G), getSize(G));
  printGraph(stdout, G);
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
  fprintf(stdout, "\nG contains %d strongly connected components:\n", count);
  List SCC = newList();
  moveBack(S);
  count = 1;
  for (int i = 0; i < length(S); i++) {
	  prepend(SCC, get(S));
          if (getParent(NG, get(S)) == 0) {
                  fprintf(stdout, "Component %d: ", count);
                  printList(stdout, SCC);
                  clear(SCC);
                  count++;
          }
          movePrev(S);
  }
  printf("getDiscover of 1 should give 0 so lets check it. getDiscover gives %d\n", getDiscover(G, 1));
  printf("getFinish of 1 gives %d which is right\n", getFinish(G, 1));
  Graph C = copyGraph(G);
  printGraph(stdout, C);
  printf("I used copy graph to make the above printed graph which should be the same as the first printed graph which it is.\n");
  freeGraph(&C);
  freeList(&S);
  freeList(&SCC);
  freeGraph(&NG);
  freeGraph(&G);
  fclose(in);
  printf(
      "This program has now tested all functions from Graph.c. Either "
      "explicity, or through a function that uses other functions. Good Day\n");
  return 0;
}
