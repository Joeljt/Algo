#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

typedef struct Node Node;

typedef struct LinkedList LinkedList;

LinkedList* createList();
void destroyList(LinkedList* list);

void insert(LinkedList* list, int data);
void append(LinkedList* list, int data);
void remove(LinkedList* list, int data);

int size(LinkedList* list);
bool isEmpty(LinkedList* list);

void printList(LinkedList* list);

#endif
