#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q
        = (PriorityQueue *) calloc(1, sizeof(PriorityQueue)); // allocates memory for queue
    q->head = 0; // intializes head and tail to 0
    q->tail = 0;
    q->capacity = capacity; // sets queue capacity to specified capacity
    q->size = 0; // intializes size to 0
    q->items = (Node **) calloc(capacity, sizeof(Node *)); // allocates memory for items in queue
    if (!q->items) { // if unsuccessful in allocation for items
        free(q); // frees pointers
        q = NULL; // sets pointer to NULL
    }
    return q; // return q
}

void pq_delete(PriorityQueue **q) {
    for (uint32_t i = (*q)->head; i < (*q)->tail; i++) {
        node_delete(&(*q)->items[i]);
    }
    free((*q)->items); // free memory for items
    free(*q); // frees pointer
    *q = NULL; // sets pointer to NULL
    return;
}

bool pq_empty(PriorityQueue *q) { // return true if size is 0
    return ((q->size) == 0);
}

bool pq_full(PriorityQueue *q) { // return true if size == capacity because capacity is max size
    return ((q->size) == (q->capacity));
}

uint32_t pq_size(PriorityQueue *q) { // returns size of queue
    return (q->size);
}

bool enqueue(PriorityQueue *q, Node *n) {
    uint32_t slot = q->tail;
    if (pq_full(q)) { // checks if queue is full
        return false; // if so return false
    }
    if (pq_empty(q)) { // if queue is empty
        q->items[q->tail] = n; // sets current slot to enqueueing node
        q->tail = (q->tail + 1) % (q->capacity); // moves tail up by 1
        q->size += 1; // increases size by 1
        return true;
    } else {
        // checks if frequency of node before current slot
        // is greater than enqueueing node. If so, then copies that node to current slot and
        // moves current slot back 1, then checks again. Does this until slot = head or previous node frequency is less than
        // enqueueing node
        while (((q->items[(slot - 1 + q->capacity) % (q->capacity)]->frequency) > (n->frequency))
               && (slot != q->head)) {
            q->items[slot] = q->items[(slot - 1 + q->capacity) % (q->capacity)];
            slot = ((slot - 1 + q->capacity) % (q->capacity));
        }
        q->items[slot] = n; // sets current slot in queue to enqueueing node
        q->tail = (q->tail + 1) % (q->capacity); // moves tail up by 1
        q->size += 1; // increases size by 1
        return true;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) { // checks if queue is empty
        return false;
    }
    *n = q->items[q->head]; // sets node n to node from queue
    q->head = (q->head + 1) % (q->capacity); // moves head up 1
    q->size -= 1; // decreases size by 1
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = q->head; i != ((q->tail - 1 + q->capacity) % q->capacity);
         i = ((i + 1) % (q->capacity))) { // prints all nodes from head to tail - 1
        node_print(q->items[i]);
    }
    return;
}
