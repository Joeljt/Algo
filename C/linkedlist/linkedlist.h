#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

Node* buildOneTwoThree();
Node* buildWithSpecialCase();
Node* buildWithDummyHead();
Node* buildWithLocalReference();

int length(Node * head);

void printLinkedList(Node *head);

void addFirst(Node** headRef, int data);
void addLast(Node** headRef, int data);
void addLastTheHardWay(Node** headRef, int data);

#endif  