#ifndef CIRCULAR_LINKEDLIST_H
#define CIRCULAR_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct CircularLinkedList CircularLinkedList;

CircularLinkedList* cl_create();
void cl_destroy(CircularLinkedList *list);

void cl_add(CircularLinkedList *list, int value, int index);
int cl_remove(CircularLinkedList *list, int index);
int cl_get(CircularLinkedList *list, int index);

void cl_print(CircularLinkedList *list);

#endif