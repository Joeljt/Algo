#include <stdlib.h>
#include <stdio.h>
#include "array_stack.h"

struct ArrayStack {
  Array* array;
};

ArrayStack* createArrayStack(int capacity) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (stack != NULL) {
        stack->array = createArray(capacity);
        if (stack->array == NULL) {
            free(stack);
            return NULL;
        }
    }
    return stack;
}

void destroyArrayStack(ArrayStack* stack) {
    if (stack != NULL) {
      destroyArray(stack->array);
      free(stack);
    }
}

void pushArrayStack(ArrayStack* stack, int value) {
  addLast(stack->array, value);
}

int popArrayStack(ArrayStack* stack) {
  return removeLast(stack->array);
}

int peekArrayStack(ArrayStack* stack) {
  return getElement(stack->array, getSize(stack->array) - 1);
}

void printArrayStack(ArrayStack* stack) {
  printf("AS: [");
  for (int i = 0; i < getSize(stack->array); i++) {
    printf("%d", getElement(stack->array, i));
    if (i != getSize(stack->array) - 1) {
      printf(", ");
    }
  }
  printf("] top\n");
}