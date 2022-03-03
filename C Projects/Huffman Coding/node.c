#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) calloc(1, sizeof(Node)); // allocates memory for node n
    n->symbol = symbol; // sets node symbol to symbol
    n->frequency = frequency; // sets node frequency to frequency
    n->left = NULL; // sets left node pointer to NULL
    n->right = NULL; // sets right node pointer to NULL
    return n;
}

void node_delete(Node **n) {
    free(*n); // free node pointer
    *n = NULL; // sets node pointer to NULL
    return;
}

Node *node_join(Node *left, Node *right) {
    uint64_t lf = left->frequency; // gets left node frequency
    uint64_t rf = right->frequency; // gets right node frequency
    uint64_t f = lf + rf; // adds left and right frequency to parent node frequency
    uint8_t s = '$'; // sets symbol to $
    Node *n = node_create(s, f); // creates new parent node n
    n->left = left; // sets left child node to Node *left
    n->right = right; // sets right child node to Node *right
    return n; // returns new parent Node n
}

void node_print(Node *n) {
    if (n->left != NULL) { // prints all left child nodes if there are any
        node_print(n->left);
    }
    if (n->right != NULL) { // prints all right child nodes if there are any
        node_print(n->right);
    }
    printf("Symbol is "); // prints u8 symbol
    printf("%" PRIu8, n->symbol);
    printf("\n");
    printf("Frequency is "); // prints u64 frequency
    printf("%" PRIu64, n->frequency);
    printf("\n");
    return;
}
