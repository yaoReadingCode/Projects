#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
#define BLOCK   4096

uint32_t rc = 0;
uint32_t counter = 0;

void DFS(Graph *G, uint32_t v, Path *C, Path *S, uint32_t vertices, uint32_t counter, bool verbose,
    char *cities[], FILE *outfile) {
    graph_mark_visited(G, v); // marks inputed vertex as visited
    counter += 1; // adds 1 to vertices visited
    path_push_vertex(C, v, G); // pushes vertice onto path and stack
    for (uint32_t w = 0; w < vertices; w++) { // for all vertices
        if (graph_has_edge(
                G, v, w)) { // if there is an edge, as in weight between two vertices is not 0
            if (!graph_visited(G, w)) { // if the vertice has not been visited yet
                rc += 1; // regression counter
                if ((path_length(C)) > (path_length(S))) {
                    rc = rc - 1;
                }
                DFS(G, w, C, S, vertices, counter, verbose, cities,
                    outfile); // recursion on new vertice
            }
            if (w == START_VERTEX
                && counter
                       == (vertices)) { // if next vertice is origin and counter is equal to number of vertices, then hamiltonian path has been found
                path_push_vertex(C, w, G); // pushes origin vertex on path again
                if (path_length(S)
                    == 0) { // if this is the first hamiltonian path, then it becomes the shortest path
                    path_copy(S, C); // copies current path onto shortest path
                    if (verbose) { // if verbose, then prints the path
                        printf("Path Length: %" PRIu32 "\n", path_length(C));
                        path_print(C, outfile, cities);
                    }
                    path_pop_vertex(C, &w, G); // pops origin path
                } else {
                    if (path_length(C)
                        < path_length(S)) { // if current path is shorter than shortest path
                        if (verbose) { // if verbose, then prints out all shortest paths as they are updated
                            printf("Path Length: %" PRIu32 "\n", path_length(C));
                            path_print(C, outfile, cities);
                            path_copy(S, C); // copies current path onto shortest
                            path_pop_vertex(C, &w, G); // pops origin
                        } else {
                            path_copy(S, C); // if not verbose ^^
                            path_pop_vertex(C, &w, G);
                        }
                    } else {
                        path_pop_vertex(C, &w, G);
                    }
                }
            }
        }
    }
    counter = counter - 1; // decreases counter by 1 if backtracking
    graph_mark_unvisited(G, v); // unmarking current vertice as unvisited if backtracking
    path_pop_vertex(C, &v, G); // pops current vertice out of path
}

int main(int argc, char **argv) {
    FILE *infile = stdin; // initalizes files to std, verbose to false, and undirected to false
    FILE *outfile = stdout;
    bool verbose = false;
    bool u = false;
    char *cities[VERTICES]; // initalizes cities array to max size of macro VERTICES or 26
    Graph *
        G; // defining G, initalizing 0, setting buffer to size 4096, and initalizing vertices, i, j, k, and c
    int opt = 0;
    char buffer[BLOCK];
    uint32_t vertices = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    int c;
    Path *curr = path_create(); // creates path current and short
    Path *shor = path_create();
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // help case return all options
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n");
            printf("   ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -u              Use undirected graph.\n");
            printf("   -v              Enable verbose printing.\n");
            printf("   -h              Program usage and help.\n");
            printf("   -i              Input containing graph (default: stdin)\n");
            printf("   -o              Output of computed path (default: stdout)\n");
            return 0;
        case 'v': // sets verbose to true which means that it prints all paths in a decreasing length
            verbose = true;
            break;
        case 'u': // sets undirected to true which means that all paths are the same distance from both vertices
            u = true;
            break;
        case 'i': // sets infile to specified file
            infile = fopen(optarg, "r");
            if (infile == NULL || errno == EINVAL) {
                printf("Error: failed to open infile.\n");
                return 0;
            }
            break;
        case 'o': //   ^ but for outfile
            outfile = fopen(optarg, "w");
            if (outfile == NULL || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                fclose(outfile);
                return 0;
            }
            break;
        default: // if any different option, prints standard error and help
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("   -u              Use undirected graph.\n");
            printf("   -v              Enable verbose printing.\n");
            printf("   -h              Program usage and help.\n");
            printf("   -i              Input containing graph (default: stdin)\n");
            printf("   -o              Output of computed path (default: stdout)\n");
            break;
        }
    }
    fscanf(infile, "%" SCNu32, &vertices); // scans file for number of vertices
    if (vertices <= 1) {
        printf("There's nowhere to go.\n"); // if vertices is 0 then nothing to do
        fclose(infile); // closes infile and outfile
        fclose(outfile);
        path_delete(&shor); // frees short path, current path, and G graph
        path_delete(&curr);
        return 0;
    }
    fgets(buffer, BLOCK, infile); // scans infile into buffer
    for (uint32_t i = 0; i < vertices;
         i++) { // for all vertices, scans in the specified names for the cities
        fgets(buffer, BLOCK, infile);
        uint32_t len = strlen(buffer);
        if (buffer[len - 1]
            == '\n') { // fscanf has a new line at the end  so this portion takes that away
            buffer[len - 1] = '\0';
        }
        cities[i] = strdup(buffer); // sets cities to name
    }
    G = graph_create(vertices, u); // creates graph
    while ((c = fscanf(infile, "%" SCNu32 "%" SCNu32 "%" SCNu32, &i, &j, &k))
           != EOF) { // scans in weights for vertices
        if (c != 3) {
            printf(
                "Error: malformed edge.\n"); // if scaned in vertices doesn't contain i, j, and weight, then it returns malformed line
            for (uint32_t i = 0; i < vertices; i++) { // free array
                free(cities[i]);
            }
            fclose(infile); // closes infile and outfile
            fclose(outfile);
            path_delete(&shor); // frees short path, current path, and G graph
            path_delete(&curr);
            graph_delete(&G);
            return 0; // ends program in above error case
        }
        graph_add_edge(G, i, j, k); // adds edge to possible edges
    }
    rc = 1;
    DFS(G, START_VERTEX, curr, shor, vertices, counter, verbose, cities,
        outfile); // calls DFS which finds shortest hamiltonian path
    if (!verbose) { // if not verbose, then it prints out the path length and path
        printf("Path Length: %" PRIu32 "\n", path_length(shor));
        printf("Path: ");
        path_print(shor, outfile, cities);
    } else {
        printf("Total recursive calls: %" PRIu32 "\n", rc);
    }

    for (uint32_t i = 0; i < vertices; i++) { // free array
        free(cities[i]);
    }
    fclose(infile); // closes infile and outfile
    fclose(outfile);
    path_delete(&shor); // frees short path, current path, and G graph
    path_delete(&curr);
    graph_delete(&G);
    return 0;
}
