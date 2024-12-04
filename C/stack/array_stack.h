#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "array/array.h"

typedef struct ArrayStack ArrayStack;

ArrayStack* createArrayStack(int capacity);
void destroyArrayStack(ArrayStack* stack);

void pushArrayStack(ArrayStack* stack, int value);
int popArrayStack(ArrayStack* stack);
int peekArrayStack(ArrayStack* stack);
int isEmptyArrayStack(ArrayStack* stack);
int isFullArrayStack(ArrayStack* stack);

void printArrayStack(ArrayStack* stack);

#endif

