#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

typedef struct Node Node;

typedef struct LinkedList LinkedList;

LinkedList* createList();
void destroyList(LinkedList* list);

void add(LinkedList* list, int index, int data);
void addFirst(LinkedList* list, int data);
void addLast(LinkedList* list, int data);

int del(LinkedList* list, int index);
int delFirst(LinkedList* list);
int delLast(LinkedList* list);

int get(LinkedList* list, int index);
int getFirst(LinkedList* list);
int getLast(LinkedList* list);

void set(LinkedList* list, int index, int data);

int size(LinkedList* list);
bool isEmpty(LinkedList* list);
bool contains(LinkedList* list, int data);

void printList(LinkedList* list);

#endif
