#pragma once

#ifndef SF_LINKEDLIST_H
#define SF_LINKEDLIST_H

typedef struct Node Node;

Node* buildOneTwoThree();
Node* buildWithSpecialCase();
Node* buildWithDummyHead();
Node* buildWithLocalReference();

int sf_length(Node * head);

void sf_printLinkedList(Node *head);

void sf_addFirst(Node** headRef, int data);
void sf_addLast(Node** headRef, int data);
void sf_addLastTheHardWay(Node** headRef, int data);

#endif  