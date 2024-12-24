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

BST* bst_create() {
    BST* bst = (BST*)malloc(sizeof(BST));
    if (bst != NULL) {
        bst->root = NULL;
        bst->size = 0;
    }
    return bst;
}

void bst_destroy(BST* bst) {
    free(bst);
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

void bst_insert(BST* bst, int data) {
    bst->root = insertNode(bst->root, data);
    bst->size++;
}

static BSTNode* findMinNode(BSTNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static BSTNode* deleteNode(BSTNode* node, int data) {
    if (node == NULL) {
        return NULL;
    } else if (data < node->data) {
        node->left = deleteNode(node->left, data);
    } else if (data > node->data) {
        node->right = deleteNode(node->right, data);
    } else {
        // 如果左子树为空，则直接用右子树替换当前节点
        if (node->left == NULL) {
            BSTNode* rightChild = node->right;
            free(node);
            return rightChild;
        } else if (node->right == NULL) {
            // 如果右子树为空，则直接用左子树替换当前节点
            BSTNode* leftChild = node->left;
            free(node);
            return leftChild;
        } else {
            // 如果左右子树都不为空，则用右子树的最小节点或者左子树的最大节点替换当前节点
            // 然后在原本的右子树中删除这个最小节点，并让当前节点的右子树指向删除最小值后的右子树
            BSTNode* minNode = findMinNode(node->right);
            node->data = minNode->data;
            node->right = deleteNode(node->right, minNode->data);
        }
    }
    return node;
}

void bst_delete(BST* bst, int data) {
    bst->root = deleteNode(bst->root, data);
    bst->size--;
}

static bool containsNode(BSTNode* node, int data) {
    if (node == NULL) {
        return false;
    } else if (data == node->data) {
        return true;
    } else if (data < node->data) {
        return containsNode(node->left, data);
    } else {
        return containsNode(node->right, data);
    }
}

bool bst_contains(BST* bst, int data) {
    return containsNode(bst->root, data);
}

void bst_dfs(BSTNode* node) {
    if (node != NULL) {
        printf("%d(1) ", node->data);
        bst_dfs(node->left);
        printf("%d(2) ", node->data);
        bst_dfs(node->right);
        printf("%d(3) ", node->data);
    }
}

// void bst_bfs(BSTNode* node) {
//     if (node == NULL) {
//         return;
//     }
//     ArrDeque* queue = ad_create(100);
//     ad_push_back(queue, node);
//     int level = 0;
//     while (!ad_is_empty(queue)) {
//         BSTNode* current = ad_pop_front(queue);
//         printf("%d(第%d层) ", current->data, level);
//         if (current->left != NULL) {
//             ad_push_back(queue, current->left);
//         }
//         if (current->right != NULL) {
//             ad_push_back(queue, current->right);
//         }
        
//     }
//     ad_destroy(queue);
// }

void bst_bfs(BSTNode* node) {
    if (node == NULL) {
        return;
    }
    ArrDeque* queue = ad_create(100);
    ad_push_back(queue, node);
    int level = 0;
    
    while (!ad_is_empty(queue)) {
        // 获取当前层的节点数量
        int levelSize = ad_size(queue);
        
        // 处理当前层的所有节点
        for (int i = 0; i < levelSize; i++) {
            BSTNode* current = ad_pop_front(queue);
            printf("%d(%d) ", current->data, level);
            
            if (current->left != NULL) {
                ad_push_back(queue, current->left);
            }
            if (current->right != NULL) {
                ad_push_back(queue, current->right);
            }
        }
        
        // 当前层处理完毕，层数加1
        level++;
    }
    
    ad_destroy(queue);
}

void bst_print(BST* bst) {
    printf("BFS:\n");
    bst_bfs(bst->root);
    printf("\n");
    printf("DFS:\n");
    bst_dfs(bst->root);
    printf("\n");
}
