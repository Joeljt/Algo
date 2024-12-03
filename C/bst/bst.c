#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

struct BST {
    BSTNode* root;
    int size;
};

static BSTNode* createBSTNode(int data) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node != NULL) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static BSTNode* insertNode(BSTNode* node, int data) {
    if (node == NULL) {
        return createBSTNode(data);
    } else if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else {
        node->right = insertNode(node->right, data);
    }
    return node;
}

static bool searchNode(BSTNode* node, int data) {
    if (node == NULL) {
        return false;
    } else if (data == node->data) {
        return true;
    } else if (data < node->data) {
        return searchNode(node->left, data);
    } else {
        return searchNode(node->right, data);
    }
}

BST* createBST() {
    BST* bst = (BST*)malloc(sizeof(BST));
    if (bst != NULL) {
        bst->root = NULL;
        bst->size = 0;
    }
    return bst;
}

void destroyBST(BST* bst) {

    free(bst);
}


int getSize(BST* bst) {
    return bst->size;
}

bool isEmpty(BST* bst) {
    return bst->size == 0;
}

void insert(BST* bst, int data) {
    bst->root = insertNode(bst->root, data);
    bst->size++;
}

bool search(BST* bst, int data) {
    return searchNode(bst->root, data);
}

void preorder(BSTNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void inorder(BSTNode* node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

void postorder(BSTNode* node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

void printNode(BSTNode* node) {
    if (node == NULL) return;
    printf("%d(左) ", node->data);
    printNode(node->left);
    printf("%d(中) ", node->data);
    printNode(node->right);
    printf("%d(右) ", node->data);
}

void print(BST* bst) {
    // preorder(bst->root);
    // inorder(bst->root);
    // postorder(bst->root);
    printNode(bst->root);
}

