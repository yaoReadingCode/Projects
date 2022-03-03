#include "universe.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe { // creates object universe
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(int rows, int cols,
    bool toroidal) { // sets rows and columns in universe to specified amount.
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *)); // allocates memory for rows with
        // each rows being a bool value
    for (int r = 0; r < rows; r += 1) {
        u->grid[r]
            = (bool *) calloc(cols, sizeof(bool)); // allocates memory for columns within each row.
        // Each cell is a bool value
    }
    return u;
}

void uv_delete(Universe *u) { // de-allocates memory starting from inner most data to
    // pointer. Must dump out water before scrapping bucket
    int rows = (u->rows);
    for (int r = 0; r < rows; r += 1) {
        free(u->grid[r]);
    }
    free(u->grid);
    free(u);
    return;
}

int uv_rows(Universe *u) { // provided by Eugene
    return u->rows;
}

int uv_columns(Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, int r,
    int c) { // sets cell at row r and column c to true, or alive.
    if ((r < u->rows) && (r >= 0)) {
        if ((c < u->cols) && (c >= 0)) {
            u->grid[r][c] = true;
        }
    }
}

void uv_dead_cell(Universe *u, int r,
    int c) { // sets cell at row r and column c to false, or dead
    if ((r < (u->rows)) && (r >= 0)) {
        if ((c < (u->cols)) && (c >= 0)) {
            u->grid[r][c] = false;
        }
    }
}

bool uv_get_cell(Universe *u, int r,
    int c) { // return bool value for cell at row r and column c.
    // If out of bounds, then returns false
    if ((r < u->rows) && (r >= 0)) {
        if ((c < u->cols) && (c >= 0)) {
            return u->grid[r][c];
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool uv_populate(Universe *u,
    FILE *infile) { // initalizes cells in  universe with data from infile
    int r = 0;
    int c = 0;
    while ((fscanf(infile, "%d %d", &r, &c))
           != -1) { // reads through inputs from infile and loops through to set
        // those values to true. If input out of bounds return false
        if ((r < u->rows) && (r >= 0)) {
            if ((c < u->cols) && (c >= 0)) {
                u->grid[r][c] = true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int uv_census(Universe *u, int r,
    int c) { // return number of neighbors surounding cell at row r
    // and column c that are alive
    int live = 0;
    int i;
    int j;
    int rows = (u->rows);
    int cols = (u->cols);
    if (u->toroidal == true) { // if toroidal, then neighbors wrap around to other side to check
        for (i = (r - 1); i <= (r + 1); i += 1) { // loops through surounding rows
            for (j = (c - 1); j <= (c + 1); j += 1) { // loops through surounding columns
                if (!((i == ((r + rows) % rows)) && (j == ((c + cols) % cols)))
                    && // skips original cell and checks if neighbor is
                    // alive. If it is then it adds one to live variable
                    (uv_get_cell(u, ((i + rows) % rows), ((j + cols) % cols)) == true)) {
                    live += 1;
                }
            }
        }
    } else { // if toroidal is false, then does same thing as above but does not
        // wrap to other side. ex. zero, zero only has three neighbors
        for (i = (r - 1); i <= (r + 1); i += 1) {
            for (j = (c - 1); j <= (c + 1); j += 1) {
                if (!((i == r) && (j == c)) && (uv_get_cell(u, i, j) == true)) {
                    live += 1;
                }
            }
        }
    }
    return live;
}

void uv_print(Universe *u, FILE *outfile) {
    int rows = (u->rows);
    int cols = (u->cols);
    for (int i = 0; i < rows;
         i += 1) { // loops through all cells and if they are alive, then it put a o.
        // If dead, then it puts a .' after all columns, goes to next line
        for (int j = 0; j < cols; j += 1) {
            if (u->grid[i][j] == true) {
                fputc('o', outfile);
            } else {
                fputc('.', outfile);
            }
        }
        fputc('\n', outfile);
    }
}
