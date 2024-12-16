#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "array/array.h"

typedef struct ArrayQueue ArrayQueue;

ArrayQueue* createArrayQueue();
void destroyArrayQueue(ArrayQueue* queue);

void enqueueArrayQueue(ArrayQueue* queue, int value);
int dequeueArrayQueue(ArrayQueue* queue);
int peekArrayQueue(ArrayQueue* queue);

void printArrayQueue(ArrayQueue* queue);

#endif