#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
    Node* current = list->head;
    while(current != NULL) {
      Node* next = current->next;
      free(current);
      current = next;
    }
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
  assert(list != NULL);
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->data = data;
    newNode->next = NULL;
    Node* current = list->head;
    if (current == NULL) {
      list->head = newNode;
    } else {
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = newNode; 
    }
    list->size ++;
  }
}

// remove 的重点在于找到目标结点的前一个结点，然后把链表断开
void remove(LinkedList* list, int data) {
  assert(list != NULL);
  assert(list->head != NULL);
  
}
