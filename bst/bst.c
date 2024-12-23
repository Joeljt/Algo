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

// 插入节点
// 通过直接返回插入的节点，可以很方便地用递归来处理整个插入动作
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
