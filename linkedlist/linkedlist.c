#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"

struct Node {
  int data;
  Node* next;
};

struct LinkedList {
  Node* dummy;
  int size;
};

static void check(LinkedList* list, int index) {
  assert(list != NULL);
  // assert(index >= 0 && index <= list->size);
}

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
    list->dummy = createNode(-1, NULL);
    list->size = 0;
    return list;
  }
  return NULL;
}

void destroyList(LinkedList* list) {
  if (list != NULL) {
    Node* current = list->dummy;
    while(current != NULL) {
      Node* next = current->next;
      free(current);
      current = next;
    }
    free(list);
  }
}

// 找到目标位置的前一个位置，断开链接
// Node* node = new Node(data); 
// node.next = prev.next;
// prev.next = node;
void add(LinkedList* list, int index, int data) {
  check(list, index);
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;
  prev->next = createNode(data, prev->next);
  list->size ++;
}

void addFirst(LinkedList* list, int data) {
  add(list, 0, data);
}

void addLast(LinkedList* list, int data) {
  add(list, list->size, data);
}

int del(LinkedList* list, int index) {
  check(list, index);
  Node* prev = list->dummy;
  for (int i = 0; i < index; i++)
    prev = prev->next;

  Node* target = prev->next; // 找到目标元素的前一个元素
  prev->next = target->next; // 跳过目标元素进行链接
  target->next = NULL; // 断开目标元素对下一个结点的指针引用

  list->size --;
  return target->data;
}

int delFirst(LinkedList* list) {
  return del(list, 0);
}

int delLast(LinkedList* list) {
  return del(list, list->size - 1);
}

int get(LinkedList* list, int index) {
  check(list, index); 
  Node* current = list->dummy->next;
  for (int i = 0; i < index; i++)
    current = current->next;
  return current->data;
}

int getFirst(LinkedList* list) {
  return get(list, 0);
}

int getLast(LinkedList* list) {
  return get(list, list->size - 1);
}

void set(LinkedList* list, int index, int data) {
  check(list, 0);
  Node* current = list->dummy->next;
  for (int i = 0; i < index; i++)
    current = current->next;
  current->data = data;
}

int size(LinkedList* list) {
  check(list, 0);
  return list->size - 1;
}

bool isEmpty(LinkedList* list) {
  return list->dummy->next == NULL;
}

bool contains(LinkedList* list, int data) {
  check(list, 0);
  Node* current = list->dummy->next;
  while(current != NULL) {
    if (current->data == data) {
      return true;
    }
    current = current->next;
  }
  return false; 
}

void printList(LinkedList* list) {
  printf("LinkedList: ");
  for (Node* current = list->dummy->next; current != NULL; current = current->next) {
    // printf("%p->", &(current->data));
    printf("%d->", current->data);
  }
  printf("NULL\n");
}





