#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

Node* createNode(int data);
void destroyNode(Node* head);

void insert(Node** headRef, int data);
void append(Node** headRef, int data);
void deleteNode(Node** headRef, int data);

void printList(Node* head);

#endif
