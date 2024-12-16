#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdbool.h>

typedef struct LinkedQueue LinkedQueue;

LinkedQueue* lq_create();
void lq_destroy(LinkedQueue* queue);

void lq_enqueue(LinkedQueue* queue, int value);
int lq_dequeue(LinkedQueue* queue);
int lq_peek(LinkedQueue* queue);

bool lq_isEmpty(LinkedQueue* queue);
void lq_print(LinkedQueue* queue);

#endif