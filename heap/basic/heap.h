#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

Heap* heap_create(int capacity, int (*compare)(void*, void*));
void heap_destroy(Heap* heap);

void heap_push(Heap* heap, void* value);
void* heap_pop(Heap* heap);
void* heap_peek(Heap* heap);

void heap_print(Heap* heap);

#endif
