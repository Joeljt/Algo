#include <stdio.h>
#include "arr/array_stack.h"
#include "linked/linked_stack.h"
#include <time.h>
#define STACK_SIZE 100

#ifdef TEST_STACK
void test_array_stack() {
    clock_t start = clock();

    ArrayStack* stack = createArrayStack(STACK_SIZE);

    for (int i = 0; i < STACK_SIZE; i++) {
        pushArrayStack(stack, i);
    }
    for (int i = 0; i < STACK_SIZE; i++) {
        popArrayStack(stack);
    }

    destroyArrayStack(stack);

    clock_t end = clock();

    double timeInSec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("ArrayStack: %.5fs\n", timeInSec);
}

void test_linked_stack() {
    clock_t start1 = clock();

    LinkedStack* stack = ls_create();

    for (int i = 0; i < STACK_SIZE; i++) {
        ls_push(stack, i);
    }
    for (int i = 0; i < STACK_SIZE; i++) {
        ls_pop(stack);
    }

    ls_destroy(stack);

    clock_t end1 = clock();

    double timeInSec1 = (double)(end1 - start1) / CLOCKS_PER_SEC;

    printf("LinkedStack: %.5fs\n", timeInSec1);

}

int main() {
    test_array_stack();
    test_linked_stack();
    return 0;
}
#endif