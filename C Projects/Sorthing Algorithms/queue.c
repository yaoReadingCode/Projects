#include "queue.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

Queue *queue_create(uint32_t capacity) { // variation of code provided by teacher. Creates a queue
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->head = 0;
    q->tail = 0;
    q->capacity = capacity;
    q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
    q->size = 0;
    if (!q->items) {
        free(q);
        q = NULL;
    }
    return q;
}

void queue_delete(Queue **q) { // variation of code provided by teacher. deletes a queue struct
    free((*q)->items);
    free(*q);
    *q = NULL;
    return;
}

bool queue_empty(Queue *q) { // checks if queue if empty. Only used in this file.
    return ((q->head) == (q->tail));
}

bool queue_full(Queue *q) { // checks if queue is full. Only used in this file.
    return (((q->head - 1) % (q->capacity)) == (q->tail));
}

uint32_t queue_size(Queue *q) { // returns number of items in queue
    return q->size;
}

bool enqueue(Queue *q,
    int64_t x) { // enqueue value on queue. If queue is full prior to enqueueing, returns false.
    if (queue_full(q)) {
        return false;
    }
    q->items[q->tail] = x;
    q->tail = (q->tail + 1) % (q->capacity);
    q->size += 1;
    return true;
}

bool dequeue(Queue *q,
    int64_t *x) { // dequeues value on queue. If queue is empty prior to dequeueing, returns false.
    if (queue_empty(q)) {
        return false;
    }
    *x = q->items[q->head];
    q->head = (q->head + 1) % (q->capacity);
    q->size -= 1;
    return true;
}

void queue_print(Queue *q) { // variation of code provided by Eugene
    printf("[");
    for (uint32_t i = q->head; i != q->tail; i = ((i + 1) % (q->capacity))) {
        printf("%" PRId64, q->items[i]);
        if (((i + 1) % (q->capacity)) != (q->tail)) {
            printf(", ");
        }
    }
    printf("]\n");
}
