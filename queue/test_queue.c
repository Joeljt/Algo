#include <stdio.h>
#include "arr/array_queue.h"
#include "linked/linked_queue.h"
#include <time.h>

#define QUEUE_SIZE 10000

#ifdef TEST_QUEUE
void test_array_queue() {

    clock_t start = clock();

    ArrayQueue* queue = aq_create();

    for (int i = 0; i < QUEUE_SIZE; i++) {
        aq_enqueue(queue, i);
    }
    for (int i = 0; i < QUEUE_SIZE; i++) {
        aq_dequeue(queue);
    }

    aq_destroy(queue);

    clock_t end = clock();

    double timeInSec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("ArrayQueue: %.5fs\n", timeInSec);
}

void test_linked_queue() {
    clock_t start = clock();

    LinkedQueue* queue = lq_create();

    for (int i = 0; i < QUEUE_SIZE; i++) {
        lq_enqueue(queue, i);
    }

    for (int i = 0; i < QUEUE_SIZE; i++) {
        lq_dequeue(queue);
    }

    lq_destroy(queue);

    clock_t end = clock();

    double timeInSec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("LinkedQueue: %.5fs\n", timeInSec);
}

int main() {
    test_array_queue();
    test_linked_queue();
    return 0;
}
#endif