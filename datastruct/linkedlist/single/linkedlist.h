#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

typedef struct LNode LNode;

typedef struct LinkedList LinkedList;

LinkedList* ll_create();
void ll_destroy(LinkedList* list);

void ll_add(LinkedList* list, int index, int data);
void ll_addFirst(LinkedList* list, int data);
void ll_addLast(LinkedList* list, int data);

int ll_del(LinkedList* list, int index);
int ll_delFirst(LinkedList* list);
int ll_delLast(LinkedList* list);

int ll_get(LinkedList* list, int index);
int ll_getFirst(LinkedList* list);
int ll_getLast(LinkedList* list);

void ll_set(LinkedList* list, int index, int data);

int ll_size(LinkedList* list);
bool ll_isEmpty(LinkedList* list);
bool ll_contains(LinkedList* list, int data);

void ll_printList(LinkedList* list);

#endif