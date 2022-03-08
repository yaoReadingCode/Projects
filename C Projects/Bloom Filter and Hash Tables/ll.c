#include "ll.h"

#include "node.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    // provided by the teacher
    uint32_t length;
    Node *head; // Head sentinel node.
    Node *tail; // Tail sentinel node.
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    // allocates memory for linked lists
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->length = 0;
    ll->mtf = mtf;
    return ll;
}

void ll_delete(LinkedList **ll) {
    // goes through linked lists and deletes nodes
    while ((*ll)->head != NULL) {
        Node *curr = (*ll)->head;
        (*ll)->head = (*ll)->head->next;
        node_delete(&curr);
    }
    // frees linked list
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

uint64_t links = 0;
uint64_t seeks = 0;

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks += 1;
    Node *curr = ll->head->next;
    while (curr != ll->tail) {
        if (!(strcmp(curr->oldspeak, oldspeak))) {
            // if mtf is present, then moves looked up node to front
            if (ll->mtf) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->prev = ll->head;
                curr->next = ll->head->next;
                ll->head->next = curr;
                curr->next->prev = curr;
            }
            return curr;
        }
        links += 1;
        curr = curr->next;
    }
    // returns null if word hasn't been found in list
    if ((curr == ll->tail) && (curr->oldspeak != oldspeak)) {
        return NULL;
    }
    // return node if it was found
    return curr;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // checks if word is in list
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }
    // inserts node into list at head by attaching prev to head and next to head next then detaching head next
    // and head next prev links and attaching them to node you want to insert
    Node *n = node_create(oldspeak, newspeak);
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->length += 1;
    ll->head->next = n;
    n->next->prev = n;
    return;
}

void ll_print(LinkedList *ll) {
    // prints node
    Node *p = ll->head->next;
    while (p != ll->tail) {
        node_print(p);
        p = p->next;
    }
    return;
}
