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
  assert(index >= 0);
}

// 模拟 new Node() 的行为
// 实际上 new Node 在做的也正是在堆区开空间并返回指针这个动作
Node* ll_createNode(int data, Node* next) {
  Node* node = (Node*)malloc(sizeof(Node));
  if (node != NULL) {
    node->data = data;
    node->next = next;
    return node;
  }
  return NULL;
}

LinkedList* ll_create() {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  if (list != NULL) {
    list->dummy = ll_createNode(-1, NULL);
    list->size = 0;
    return list;
  }
  return NULL;
}

void ll_destroy(LinkedList* list) {
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
void ll_add(LinkedList* list, int index, int data) {
  check(list, index);
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;
  prev->next = ll_createNode(data, prev->next);
  list->size ++;
}

void ll_addFirst(LinkedList* list, int data) {
  ll_add(list, 0, data);
}

void ll_addLast(LinkedList* list, int data) {
  ll_add(list, list->size, data);
}

int ll_del(LinkedList* list, int index) {
  check(list, index);
  Node* prev = list->dummy;
  for (int i = 0; i < index; i++)
    prev = prev->next;

  Node* target = prev->next; // 找到目标元素的前一个元素
  int value = target->data;
  prev->next = target->next; // 跳过目标元素进行链接
  target->next = NULL; // 断开目标元素对下一个结点的指针引用
  free(target); // !!! 释放节点所占用的内存

  list->size --;
  return value;
}

int ll_delFirst(LinkedList* list) {
  return ll_del(list, 0);
}

int ll_delLast(LinkedList* list) {
  return ll_del(list, list->size - 1);
}

int ll_get(LinkedList* list, int index) {
  check(list, index); 
  Node* current = list->dummy->next;
  for (int i = 0; i < index; i++)
    current = current->next;
  return current->data;
}

int ll_getFirst(LinkedList* list) {
  return ll_get(list, 0);
}

int ll_getLast(LinkedList* list) {
  return ll_get(list, list->size - 1);
}

void ll_set(LinkedList* list, int index, int data) {
  check(list, 0);
  Node* current = list->dummy->next;
  for (int i = 0; i < index; i++)
    current = current->next;
  current->data = data;
}

int ll_size(LinkedList* list) {
  check(list, 0);
  return list->size - 1;
}

bool ll_isEmpty(LinkedList* list) {
  return list->dummy->next == NULL;
}

bool ll_contains(LinkedList* list, int data) {
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

void ll_printList(LinkedList* list) {
  // printf("LinkedList: ");
  for (Node* current = list->dummy->next; current != NULL; current = current->next) {
    // printf("%p->", &(current->data));
    printf("%d->", current->data);
  }
  printf("NULL\n");
}





