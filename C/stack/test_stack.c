#include <stdio.h>
#include "array_stack.h"

#ifdef TEST_STACK
int main() {
    ArrayStack* stack = createArrayStack(10);

    for (int i = 0; i < 20; i++) {
        pushArrayStack(stack, i);
        printArrayStack(stack);
    }

    popArrayStack(stack);
    printArrayStack(stack);

    popArrayStack(stack);
    printArrayStack(stack);

    popArrayStack(stack);
    printArrayStack(stack);

    pushArrayStack(stack, 100);
    printArrayStack(stack);

    printf("peek: %d\n", peekArrayStack(stack));

    destroyArrayStack(stack);

    return 0;
}
#endif