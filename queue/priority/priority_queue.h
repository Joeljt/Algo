#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../../heap/basic/heap.h"

typedef Heap PriorityQueue;

PriorityQueue* pq_create(int capacity, int (*compare)(void*, void*));
void pq_destroy(PriorityQueue* pq);

void pq_push(PriorityQueue* pq, void* value);
void* pq_pop(PriorityQueue* pq);
void* pq_peek(PriorityQueue* pq);

void pq_print(PriorityQueue* pq);

#endif