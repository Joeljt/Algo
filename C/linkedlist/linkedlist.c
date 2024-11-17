#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct Node {
    int data;
    struct Node* next;
};

static void push(Node** nodeRef, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *nodeRef; // 把新结点指向当前 head 节点
    *nodeRef = newNode; // 把当前结点变成新的 head 节点
}

struct Node* buildOneTwoThree() {
    Node* head = (Node*)malloc(sizeof(Node));
    Node* second = (Node*)malloc(sizeof(Node));
    Node* third = (Node*)malloc(sizeof(Node));

    head->data = 1;
    second->data = 2;
    third->data = 3;

    third->next = NULL;
    second->next = third;
    head->next = second;

    return head;
}

struct Node* buildWithSpecialCase() {
    Node* head = NULL;
    Node* tail;
    int i;

    // 单独处理第一个元素
    push(&head, 1);
    tail = head;

    // 然后利用 push 方法向最后一个位置插入元素
    for (i = 2; i < 10; i++) {
       push(&(tail->next), i);
       tail = tail->next; 
    }

    return head; 
}

struct Node* buildWithDummyHead() {
    // 注意 dummy 不是指针
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    for (int i = 0; i < 10; i++) {
       push(&(tail->next), i);
       tail = tail->next; 
    }
    // dummy.next 才是真正的头节点 
    return dummy.next;
}

struct Node* buildWithLocalReference() {
    Node* head = NULL;
    Node** lastPtr = &head;

    for (int i = 0; i < 7; i++){
        push(lastPtr, i); // 直接传引用进去更新，然后外面维护引用
        lastPtr = &((*lastPtr)->next);
    }

    return head; 
}


int length(Node * head) {
    Node* current = head;
    int count = 0;
    while (current != NULL) {
        count ++;
        current = current->next; 
    }
    return count; 
}

void addFirst(Node** head, int data) {
    push(head, data);
}

void addLast(Node **head, int data) {
    Node* current = *head;
    if (current == NULL) {
        push(head, data);
    } else {
        while(current->next != NULL) {
            current = current->next;
        }
        push(&(current->next), data);
    }
}

void addLastTheHardWay(Node** head, int data) {
    Node* current = *head;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (current == NULL) {
        *head = newNode;
    } else {
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printLinkedList(Node *head) {
    printf("LinkedList: ");    
    Node *current = head;
    for (; current != NULL; current = current->next) {
        printf("%d -> ", current->data);
    }
    printf("NULL (%d)\n", length(head));
}
