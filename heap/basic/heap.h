#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

Heap* heap_create(int capacity);
void heap_destroy(Heap* heap);

void heap_push(Heap* heap, int value);
int heap_pop(Heap* heap);
int heap_peek(Heap* heap);

void heap_print(Heap* heap);

#endif
