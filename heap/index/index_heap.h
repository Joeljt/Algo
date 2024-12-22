#ifndef INDEX_HEAP_H
#define INDEX_HEAP_H

#include "stdio.h"
#include "stdlib.h"

typedef struct IndexHeap IndexHeap;

IndexHeap* ih_create(int capacity);
void ih_destroy(IndexHeap* ih);

void ih_push(IndexHeap* ih, int value);
int ih_pop(IndexHeap* ih);
void ih_update(IndexHeap* ih, int index, int value);

void ih_print(IndexHeap* ih);

#endif