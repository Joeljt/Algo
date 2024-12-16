#include "circular_queue.h"
#include <stdlib.h>
#include <stdio.h>

struct CircularQueue {
    int *array;
    int front;
    int rear;
    int count;
    int size;
};

// 循环队列的扩容不能用 realloc 来实现，因为我们需要对元素位置做调整
static void resize(CircularQueue *queue, int newCapacity) {
    int *newArray = (int *)malloc((newCapacity + 1) * sizeof(int));
    if (newArray == NULL) {
        return;
    }
    for (int i = 0; i < queue->count; i++) {
        newArray[i] = queue->array[(queue->front + i) % queue->size];
    }
    free(queue->array);
    queue->array = newArray;
    queue->size = newCapacity + 1;
    queue->front = 0;
    queue->rear = queue->count;
}

CircularQueue *cq_create(int size) {
    CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    queue->array = (int *)malloc((size + 1) * sizeof(int));
    queue->size = size + 1;
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    return queue;
}

void cq_destroy(CircularQueue *queue) {
    if (queue == NULL) {
        return;
    }
    free(queue->array);
    free(queue);
}

bool cq_isEmpty(CircularQueue *queue) {
    return queue->front == queue->rear;
}

bool cq_isFull(CircularQueue *queue) {
    return ((queue->rear + 1) % queue->size) == queue->front;
}

void cq_enqueue(CircularQueue *queue, int value) {
    if (cq_isFull(queue)) {
        resize(queue, queue->count * 2);
    }
    queue->array[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->size;
    queue->count++;
}

int cq_dequeue(CircularQueue *queue) {
    if (cq_isEmpty(queue)) {
        return -1;
    }
    int value = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    queue->count--;
    if (queue->count < queue->count / 4 && queue->count / 2 != 0) {
        resize(queue, queue->count / 2);
    }
    return value;
}

void cq_print(CircularQueue *queue) {
    printf("CQ: front[");
    for (int i = queue->front; i != queue->rear; i = (i + 1) % queue->size) {
        printf("%d(%d)", queue->array[i], i);
        if ((i + 1) % queue->size != queue->rear) {
            printf(", ");
        }
    }
    printf("] rear\n");
}
