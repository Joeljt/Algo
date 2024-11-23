#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

struct Node {
  int data;
  Node* next;
};

struct LinkedList {
  Node* head;
  int size;
};

LinkedList* createList() {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  if (list != NULL) {
    list->head = NULL;
    list->size = 0;
    return list;
  }
  return NULL;
}

void destroyList(LinkedList* list) {
  if (list != NULL) {
    free(list);
  }
}

void insert(LinkedList* list, int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
  }
}

void append(LinkedList* list, int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->data = data;
    if (list->head == NULL) {
      newNode->next = NULL;
      list->head = newNode;
    } else {
      Node* current = list->head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = newNode;
      newNode->next = NULL;
    }
    list->size++;
  }
}

void remove(LinkedList* list, int data) {
  if (list != NULL) {
    
  }
}
