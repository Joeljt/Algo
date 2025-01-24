#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_stack.h"

struct LinkedStack {
    LinkedList* list;
};

LinkedStack* ls_create() {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (stack != NULL) {
        stack->list = ll_create();
        return stack;
    }
    return NULL;
}

void ls_destroy(LinkedStack* stack) {
    if (stack != NULL) {
        ll_destroy(stack->list);
        free(stack);
    }
}

void ls_push(LinkedStack* stack, int value) {
    if (stack != NULL) {
        ll_addFirst(stack->list, value);
    }
}

int ls_pop(LinkedStack* stack) {
    if (stack != NULL) {
        return ll_delFirst(stack->list);
    }
    return -1;
}

int ls_peek(LinkedStack* stack) {
    if (stack != NULL) {
        return ll_getFirst(stack->list);
    }
    return -1;
}

bool ls_isEmpty(LinkedStack* stack) {
    if (stack != NULL) {
        return ll_isEmpty(stack->list);
    }
    return true;
}

void ls_printStack(LinkedStack* stack) {
    if (stack != NULL) {
        printf("LS: top ");
        ll_printList(stack->list);
    }
}