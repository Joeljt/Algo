#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

Heap* createHeap(int capacity);
void destroyHeap(Heap* heap);

void push(Heap* heap, int value);
int pop(Heap* heap);
int peek(Heap* heap);

void printHeap(Heap* heap);

#endif
