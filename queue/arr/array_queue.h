#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "array/array.h"

typedef struct ArrayQueue ArrayQueue;

ArrayQueue* aq_create();
void aq_destroy(ArrayQueue* queue);

void aq_enqueue(ArrayQueue* queue, int value);
int aq_dequeue(ArrayQueue* queue);
int aq_peek(ArrayQueue* queue);

void aq_print(ArrayQueue* queue);

#endif
