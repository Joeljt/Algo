#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct BSTNode BSTNode;

typedef struct BST BST;

BST* bst_create();
void bst_destroy(BST* bst);


void bst_insert(BST* bst, int data);
void bst_delete(BST* bst, int data);

bool bst_search(BST* bst, int data);

void bst_preorder(BSTNode* node);
void bst_inorder(BSTNode* node);
void bst_postorder(BSTNode* node);

void bst_print(BST* bst);

#endif
