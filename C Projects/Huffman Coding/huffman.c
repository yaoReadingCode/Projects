#include "huffman.h"

#include "code.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stddef.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    uint32_t capacity = 256;
    PriorityQueue *q = pq_create(capacity); // create queue of size capacity
    for (uint64_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            Node *n = node_create(
                i, hist[i]); // if frequency of symbol is > 1 then create a node for it
            enqueue(q, n); // put it into queue
        }
    }
    //pq_print(q);
    while ((pq_size(q)) > 1) {
        // if queue is > 1 then join adjacent nodes together until root is made
        Node *left;
        Node *right;
        dequeue(q, &left); // get left and right node
        dequeue(q, &right);
        Node *joined;
        joined = node_join(left, right); // join nodes together
        enqueue(q, joined); // put new root nodes into queue
    }
    Node *root;
    dequeue(q, &root); // get root node
    pq_delete(&q); // delete queue and return root
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code c = { 0, { 0 } }; // possible error?
    if (root) {
        if ((root->left == NULL) && (root->right == NULL)) {
            // if node is a leaf then compressed code for it is c
            table[root->symbol] = c;
        } else {
            uint8_t d = 0;
            // push 0 if you go left on the tree
            code_push_bit(&c, d);
            build_codes((root->left), table);
            // delete prvious bit when you backtrack
            code_pop_bit(&c, &d);
            d = 1;
            // push 1 if you go right on tree
            code_push_bit(&c, d);
            // recursively to to node on right
            build_codes((root->right), table);
            // delete previous bit when you backtrack
            code_pop_bit(&c, &d);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create((nbytes + 1));
    for (int i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') {
            // if byte in tree dump is L then next byte is a symbol
            // create a node with that symbol
            Node *left = node_create(tree[i + 1], 0);
            // push that node onto stack
            stack_push(s, left);
            i++;
        }
        if (tree[i] == 'I') {
            // if byte in tree is an I then that means that
            // previous two nodes should be joined together
            Node *r;
            Node *l;
            stack_pop(s, &r);
            stack_pop(s, &l);
            // join two nodes together
            Node *join = node_join(l, r);
            stack_push(s, join);
        }
    } // keep doing this until you get root
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s); // free stack
    return root;
}

void delete_tree(Node **root) {
    if (root) {
        if ((*root)->left != NULL) { // recursively go through node if root node has child nodes
            delete_tree(&(*root)->left);
        }
        if ((*root)->right != NULL) { // ^^
            delete_tree(&(*root)->right);
        }
        node_delete(&(*root)); // delete node
    }
}
