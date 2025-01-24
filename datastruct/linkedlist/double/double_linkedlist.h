#ifndef DOUBLE_LINKEDLIST_H
#define DOUBLE_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct DNode DNode;

typedef struct DoubleLinkedList DoubleLinkedList;

DoubleLinkedList* dl_create();
void dl_destroy(DoubleLinkedList* list);

void dl_add(DoubleLinkedList* list, int value, int index);
int dl_remove(DoubleLinkedList* list, int index);
void dl_set(DoubleLinkedList* list, int index, int value);
int dl_get(DoubleLinkedList* list, int index);

void dl_print(DoubleLinkedList* list);

#endif