#include "priority_queue.h"

PriorityQueue* pq_create(int capacity, int (*compare)(void*, void*)) {
  return heap_create(capacity, compare);
}

void pq_destroy(PriorityQueue* pq) {
  heap_destroy(pq);
}

void pq_push(PriorityQueue* pq, void* value) {
  heap_push(pq, value);
}

void* pq_pop(PriorityQueue* pq) {
  return heap_pop(pq);
}

void* pq_peek(PriorityQueue* pq) {
  return heap_peek(pq);
}

void pq_print(PriorityQueue* pq) {
  heap_print(pq);
}