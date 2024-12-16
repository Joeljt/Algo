#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>
#include "array/array.h"

typedef struct CircularQueue CircularQueue;

CircularQueue *cq_create(int size);
void cq_destroy(CircularQueue *queue);

void cq_enqueue(CircularQueue *queue, int value);
int cq_dequeue(CircularQueue *queue);

bool cq_isEmpty(CircularQueue *queue);
bool cq_isFull(CircularQueue *queue);

void cq_print(CircularQueue *queue);

#endif
