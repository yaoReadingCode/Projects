#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"
#include "stat.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum sorting { // all sorts
    BUBBLE,
    SHELL,
    QUICK_S,
    QUICK_Q,
} sorting;

#define OPTIONS "habsqQn:p:r:o"

uint32_t compares = 0; // compare counter definition
uint32_t moves = 0; // move coounter definition
int64_t maxs = 0; // max size of stack definition
int64_t maxq = 0; // max size of queue definition

int main(int argc, char **argv) {
    int opt = 0; // initalizing variables
    Set sorts = set_empty();
    uint32_t r = 13371453;
    uint32_t n = 100;
    uint32_t p = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // -help option
            printf("SYNOPSIS\n");
            printf("A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-habsqQo] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -h              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -b              Enable Bubble Sort.\n");
            printf("   -q              Enable Quick Sort (Stack).\n");
            printf("   -Q              Enable Quick Sort (Queue).\n");
            printf("   -n length       Specify number of array elements.\n");
            printf("   -p elements     Specify number of elements to print.\n");
            printf("   -r seed         Specify random seed.\n");
            break;
        case 'a': // all option, puts all sorts into set
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, QUICK_S);
            sorts = set_insert(sorts, QUICK_Q);
            break;
        case 'b': // puts bubble sort into set
            sorts = set_insert(sorts, BUBBLE);
            break;
        case 's': // puts shell sort into set
            sorts = set_insert(sorts, SHELL);
            break;
        case 'q': // puts quick sort with stack into set
            sorts = set_insert(sorts, QUICK_S);
            break;
        case 'Q': // puts quick sort with queue into set
            sorts = set_insert(sorts, QUICK_Q);
            break;
        case 'n': // sets size of array
            n = atoi(optarg);
            break;
        case 'p': // sets number of printed elements
            p = atoi(optarg);
            break;
        case 'r': // sets random seed
            r = atoi(optarg);
            break;
        default: // defaults if error
            fprintf(stderr, " ");
            printf("SYNOPSIS\n");
            printf("A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-habsqQo] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -h              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -b              Enable Bubble Sort.\n");
            printf("   -q              Enable Quick Sort (Stack).\n");
            printf("   -Q              Enable Quick Sort (Queue).\n");
            printf("   -n length       Specify number of array elements.\n");
            printf("   -p elements     Specify number of elements to print.\n");
            printf("   -r seed         Specify random seed.\n");
            break;
        }
    }
    srand(r); // sets random seed
    uint32_t *arr = (uint32_t *) calloc(n, sizeof(uint32_t)); // creates an array
    for (uint32_t i = 0; i < n; i += 1) { // for up to set size, creates random number
        arr[i] = rand();
    }
    for (sorting i = BUBBLE; i <= QUICK_Q; i += 1) { // goes through numbers
        if (set_member(sorts, i)) { // if a number is in the set
            if (i == 0) { // if bubble sort was in set
                puts("Bubble Sort"); // prints
                compares = 0; // sets compare counter to 0
                moves = 0; // sets compare move counter to 0
                uint32_t *newarr = (uint32_t *) calloc(
                    n, sizeof(uint32_t)); // creates a replicant array to work on
                for (uint32_t x = 0; x < n; x += 1) {
                    newarr[x] = arr[x];
                    //printf("%d is in newarr.\n", newarr[x]);
                }
                bubble_sort(newarr, n); // does bubble sort on new array
                printf(
                    "%d elements, %d moves, %d compares\n", n, moves, compares); // prints out stats
                int enter = 0;
                for (uint32_t i = 0; i < p; i++) { // prints out array 5 at a time
                    printf("%13" PRIu32, newarr[i]);
                    if (enter == 4) {
                        printf("\n");
                        enter = 0;
                    } else {
                        enter++;
                    }
                }
                free(newarr);
                ; // frees new array
            }
            if (i == 1) { // if shell sort was in array
                puts("Shell Sort"); // prints
                compares = 0;
                moves = 0;
                uint32_t *newarr1 = (uint32_t *) calloc(n, sizeof(uint32_t));
                for (uint32_t x = 0; x < n; x += 1) {
                    newarr1[x] = arr[x];
                }
                shell_sort(newarr1, n); // does shell sort
                printf("%d elements, %d moves, %d compares\n", n, moves, compares);
                int enter = 0;
                for (uint32_t i = 0; i < p; i++) {
                    printf("%13" PRIu32, newarr1[i]);
                    if (enter == 4) {
                        printf("\n");
                        enter = 0;
                    } else {
                        enter++;
                    }
                }
                free(newarr1); // frees replicant array
            }
            if (i == 2) { // if quick sort with a stack was in array
                puts("Quick Sort (Stack)");
                compares = 0;
                moves = 0;
                uint32_t *newarr2 = (uint32_t *) calloc(n, sizeof(uint32_t)); //replicant array
                for (uint32_t x = 0; x < n; x += 1) {
                    newarr2[x] = arr[x];
                }
                quick_sort_stack(newarr2, n); // quick sort with a stack
                printf("%d elements, %d moves, %d compares\n", n, moves, compares); // statistics
                printf("Max Stack Size: %ld\n", maxs);
                int enter = 0;
                for (uint32_t i = 0; i < p; i++) { // prints out 5 elements at a time
                    printf("%13" PRIu32, newarr2[i]);
                    if (enter == 4) {
                        printf("\n");
                        enter = 0;
                    } else {
                        enter++;
                    }
                }
                free(newarr2); // frees new array
            }
            if (i == 3) { // if quick sort with a queue was in array
                puts("Quick Sort (Queue)");
                compares = 0;
                moves = 0;
                uint32_t *newarr3
                    = (uint32_t *) calloc(n, sizeof(uint32_t)); // creates replicant array
                for (uint32_t x = 0; x < n; x += 1) {
                    newarr3[x] = arr[x];
                }
                quick_sort_queue(newarr3, n); // quick sort with a queue
                printf("%d elements, %d moves, %d compares\n", n, moves, compares); // statistics
                printf("Max Queue Size: %ld\n", maxq);
                int enter = 0;
                for (uint32_t i = 0; i < p; i++) { // prints out elements
                    printf("%13" PRIu32, newarr3[i]);
                    if (enter == 4) {
                        printf("\n");
                        enter = 0;
                    } else {
                        enter++;
                    }
                }
                free(newarr3); //free new array
            }
        }
    }
    //for (uint32_t i = 0; i < n; i += 1) { // for up to set size, free array
    //        free(&arr[i]);
    //}
    //free(arr);
    return 0;
}
