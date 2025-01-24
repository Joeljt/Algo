#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdbool.h>

#include "linkedlist/single/linkedlist.h"

typedef struct LinkedStack LinkedStack;

LinkedStack* ls_create();
void ls_destroy(LinkedStack* stack);
void ls_push(LinkedStack* stack, int value);
int ls_pop(LinkedStack* stack);
int ls_peek(LinkedStack* stack);
bool ls_isEmpty(LinkedStack* stack);

void ls_printStack(LinkedStack* stack);

#endif