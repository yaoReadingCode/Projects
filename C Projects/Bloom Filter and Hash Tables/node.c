#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_dup(char *string) {
    // allocates memory to copy onto a different string
    char *dup = calloc(strlen(string) + 1, sizeof(char));
    if (dup != NULL) {
        strcpy(dup, string);
        return dup;
    }
    return NULL;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // allocates memory for node
    Node *n = (Node *) calloc(1, sizeof(Node));
    // if oldspeak word or newspeak word is inputted, then copies that over to node values
    if (oldspeak != NULL) {
        n->oldspeak = str_dup(oldspeak);
    } else {
        n->oldspeak = NULL;
    }
    if (newspeak != NULL) {
        n->newspeak = str_dup(newspeak);
    } else {
        n->newspeak = NULL;
    }
    // sets next and prev to null
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_delete(Node **n) {
    // delete memory for newspeak or oldspeak if they exist
    if ((*n)->newspeak != NULL) {
        free((*n)->newspeak);
    }
    if ((*n)->oldspeak != NULL) {
        free((*n)->oldspeak);
    }
    // free node
    free(*n);
    *n = NULL;
    return;
}

void node_print(Node *n) {
    // prints node checks if only oldspeak is present or both
    if ((n->oldspeak != NULL) && (n->newspeak != NULL)) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if ((n->oldspeak != NULL) && (n->newspeak == NULL)) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
