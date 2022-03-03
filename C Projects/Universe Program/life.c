#include "universe.h"

#include <errno.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:"
#define DELAY   50000

int main(int argc, char **argv) {
    FILE *infile = stdin; // initalizes files to std, toroidal to false, generations to true,
        // ncurses to true, and variables to 0
    FILE *outfile = stdout;
    bool toroidal = false;
    int generations = 100;
    int rows = 0;
    int cols = 0;
    int opt = 0;
    bool ncoff = true;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': // input of -i to specify an infile
            infile = fopen(optarg, "r");
            if (infile == NULL || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                fclose(infile);
                return 0;
            }
            break;
        case 'o': // input of -o to specify outfile
            outfile = fopen(optarg, "w");
            if (outfile == NULL || errno == EINVAL) {
                printf("Error opening %s\n", optarg);
                fclose(outfile);
                return 0;
            }
            break;
        case 't': // sets toroidal to true
            toroidal = true;
            break;
        case 'n': // specific number of generations
            generations = atoi(optarg);
            break;
        case 's': // turns ncurses, or the screen, off
            ncoff = false;
            break;
        default: // false input return standard error
            fprintf(stderr, " ");
            break;
        }
    }
    fscanf(infile, "%d %d", &rows,
        &cols); // scans infile for inital row and columns
    Universe *a = uv_create(rows, cols,
        toroidal); // creates universe a and b with specified rows and columns
    Universe *b = uv_create(rows, cols, toroidal);
    Universe *temp; // temp pointer to switch a and b
    uv_populate(a, infile);
    initscr(); // initalizes screen
    curs_set(FALSE);
    int live;
    for (int g = 0; g < generations; g += 1) { // loops for certain amount of generations
        if (ncoff == true) { // if ncurses is kept on
            noecho();
            clear();
            for (int i = 0; i < rows;
                 i += 1) { // loops through each cell and if it is alive, or true,
                // then it print o in it
                for (int j = 0; j < cols; j += 1) {
                    if (uv_get_cell(a, i, j) == true) {
                        mvprintw(i, j, "o");
                    }
                }
            }
            refresh(); // refreshes screen with new data
            usleep(DELAY); // delays by constant number delay
        }
        for (int i = 0; i < rows; i += 1) { // loops through each cell
            for (int j = 0; j < cols; j += 1) {
                live = uv_census(a, i, j);
                if ((live == 2 || live == 3)
                    && (uv_get_cell(a, i, j)
                        == true)) { // if the amount of neighbors surounding a live cell are
                    // two or three then it keep them alive in universe b
                    uv_live_cell(b, i, j);
                } else if ((live == 3)
                           && (uv_get_cell(a, i, j)
                               == false)) { // if the amount of neighbors surounding a dead
                    // cell are three then it revives them in universe
                    // b
                    uv_live_cell(b, i, j);
                } else { // if the amount of neighbors are less than two or greater than
                    // three then it kills off the cell in universe b
                    uv_dead_cell(b, i, j);
                }
            }
        }
        temp = a; // switches universe a and b pointers
        a = b;
        b = temp;
    }
    endwin(); // ends screen
    echo();
    uv_print(a, outfile);
    uv_delete(a); // deletes allocated memory for a and b
    uv_delete(b);
    fclose(infile); // closes infile and outfile
    fclose(outfile);
    return 0;
}
