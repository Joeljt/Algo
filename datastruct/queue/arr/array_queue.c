#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

struct ArrayQueue {
  Array* array;
};

ArrayQueue* aq_create() {
  ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
  if (queue != NULL) {
    queue->array = createArray(10);
  }
  return queue;
}

void aq_destroy(ArrayQueue* queue) {
  if (queue != NULL) {
    destroyArray(queue->array);
    free(queue);
  }
}

void aq_enqueue(ArrayQueue* queue, int value) {
  addLast(queue->array, value);
}

int aq_dequeue(ArrayQueue* queue) {
  return removeFirst(queue->array);
}

int aq_peek(ArrayQueue* queue) {
  return getElement(queue->array, 0);
}

void aq_print(ArrayQueue* queue) {
  printf("AQ: front [");
  for (int i = 0; i < getSize(queue->array); i++) {
    printf("%d", getElement(queue->array, i));
    if (i != getSize(queue->array) - 1) {
      printf(", ");
    }
  }
  printf("] tail\n");
}
