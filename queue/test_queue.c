#include <stdio.h>
#include "arr/array_queue.h"

#ifdef TEST_QUEUE
int main() {
    ArrayQueue* queue = createArrayQueue();

    for (int i = 0; i < 10; i++) {
        enqueueArrayQueue(queue, i);
        printArrayQueue(queue);
    }

    for (int i = 0; i < 5; i++) {
        dequeueArrayQueue(queue);
        printArrayQueue(queue);
    }

    destroyArrayQueue(queue);

    return 0;
}
#endif