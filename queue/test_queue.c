#include <stdio.h>
#include "arr/array_queue.h"
#include "linked/linked_queue.h"
#include "circular/circular_queue.h"
#include "deque/arr_deque.h"
#include "deque/ll_deque.h"
#include "priority/priority_queue.h"
#include <time.h>
#include <stdlib.h>

#define QUEUE_SIZE 100000

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

void test_circular_queue() {    
    clock_t start = clock();
    CircularQueue* queue = cq_create(QUEUE_SIZE / 100);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        cq_enqueue(queue, i);
    }

    for (int i = 0; i < QUEUE_SIZE; i++) {
        cq_dequeue(queue);
    }

    cq_destroy(queue);

    clock_t end = clock();

    double timeInSec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("CircularQueue: %.5fs\n", timeInSec);
}

void test_arr_deque() {
    ArrDeque* deque = ad_create(5);
    for (int i = 0; i < 10; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        ad_push_back(deque, value);
        ad_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        free(ad_pop_front(deque));
        ad_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        free(ad_pop_back(deque));
        ad_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        ad_push_front(deque, value);
        ad_print(deque);
    }
    
    ad_destroy(deque);
}

void test_ll_deque() {
    LinkedDeque* deque = ld_create();
    for (int i = 0; i < 10; i++) {
        ld_push_back(deque, i);
        ld_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        ld_pop_front(deque);
        ld_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        ld_pop_back(deque);
        ld_print(deque);
    }
    for (int i = 0; i < 5; i++) {
        ld_push_front(deque, i);
        ld_print(deque);
    }
    ld_destroy(deque);
}

int compare(void* a, void* b) {
    return *(int*)b - *(int*)a;
}

void test_priority_queue() {
    PriorityQueue* pq = pq_create(10, compare);
    for (int i = 0; i < 10; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        pq_push(pq, value);
        pq_print(pq);
    }
    for (int i = 0; i < 10; i++) {
        free(pq_pop(pq));
        pq_print(pq);
    }
    pq_destroy(pq);
}

int main() {
    // test_array_queue();
    // test_linked_queue();
    // test_circular_queue();
    // test_arr_deque();
    // test_ll_deque();
    test_priority_queue();
    return 0;
}
#endif
