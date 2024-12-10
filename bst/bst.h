#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct BSTNode BSTNode;

typedef struct BST BST;

BST* createBST();
void destroyBST(BST* bst);

int getSize(BST* bst);
bool isEmpty(BST* bst);

void insert(BST* bst, int data);
void delete(BST* bst, int data);

bool search(BST* bst, int data);

void preorder(BSTNode* node);
void inorder(BSTNode* node);
void postorder(BSTNode* node);

void print(BST* bst);

#endif
