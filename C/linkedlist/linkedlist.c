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

// 模拟 new Node() 的行为
// 实际上 new Node 在做的也正是在堆区开空间并返回指针这个动作
Node* createNode(int data, Node* next) {
  Node* node = (Node*)malloc(sizeof(Node));
  if (node != NULL) {
    node->data = data;
    node->next = next;
    return node;
  }
  return NULL;
}

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

// 找到目标位置的前一个位置，断开链接
void add(LinkedList* list, int index, int data) {
  assert(index >= 0 && index < list->size);
  if (index == 0) {
    addFirst(list, data);
  } else {
    Node* prev = list->head;
    for (int i = 0; i < index - 1; i++) {
      prev = prev->next;
    }
    prev->next = createNode(data, prev->next);
    list->size ++;
  }
}

void addFirst(LinkedList* list, int data) {
    // Node* node = new Node(data); 
    // node.next = prev.next;
    // prev.next = node;
    list->head = createNode(data, list->head);
    list->size++;
}

void addLast(LinkedList* list, int data) {
  add(list, list->size, data);
}


