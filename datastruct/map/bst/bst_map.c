#include "bst_map.h"
#include <stdlib.h>

typedef struct BSTMapNode {
    int key;
    int value;
    struct BSTMapNode* left;
    struct BSTMapNode* right;
} BSTMapNode;

struct BSTMap {
    BSTMapNode* root;
    int size;
};

static BSTMapNode* bm_create_node(int key, int value) {
    BSTMapNode* node = (BSTMapNode*)malloc(sizeof(BSTMapNode));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// 递归销毁节点
static void bm_destroy_node(BSTMapNode* node) {
    if (node != NULL) {
        bm_destroy_node(node->left);
        bm_destroy_node(node->right);
        free(node);
    }
}

BSTMap* bm_create() {
    BSTMap* map = (BSTMap*)malloc(sizeof(BSTMap));
    map->root = NULL;
    map->size = 0;
    return map;
}

void bm_destroy(BSTMap* map) {
    bm_destroy_node(map->root);
    free(map);
}

static BSTMapNode* bm_put_node(BSTMapNode* node, int key, int value, bool* is_insert) {
    if (node == NULL) {
        *is_insert = true;
        return bm_create_node(key, value);
    } else if (key < node->key) {
        node->left = bm_put_node(node->left, key, value, is_insert);
    } else if (key > node->key) {
        node->right = bm_put_node(node->right, key, value, is_insert);
    } else { // key == node->key
        // key 已经存在的情况下，更新节点的值
        node->value = value;
        *is_insert = false;
    }
    return node;
}

void bm_put(BSTMap* map, int key, int value) {
    // 需要根据当前是插入还是更新决定是否要更新 size
    bool is_insert = false;
    map->root = bm_put_node(map->root, key, value, &is_insert);
    if (is_insert) {
        map->size++;
    }
}

static BSTMapNode* bm_get_node(BSTMapNode* node, int key) {
    if (node == NULL) {
        return NULL;
    } else if (key < node->key) {
        return bm_get_node(node->left, key);
    } else if (key > node->key) {
        return bm_get_node(node->right, key);
    } else {
        return node;
    }
}

int bm_get(BSTMap* map, int key, int fallback) {
    BSTMapNode* node = bm_get_node(map->root, key);
    return node != NULL ? node->value : fallback;
}

static BSTMapNode* bm_find_min(BSTMapNode* node) {
    if (node != NULL) {
        while (node->left != NULL) {
            node = node->left;
        }
    }
    return node;
}

static BSTMapNode* bm_remove_node(BSTMapNode* node, int key, bool* deleted) {
    if (node == NULL) {
        return NULL;
    }
    if (key < node->key) {
        node->left = bm_remove_node(node->left, key, deleted);
    } else if (key > node->key) {
        node->right = bm_remove_node(node->right, key, deleted);
    } else {
        // 进入 else 就要标记，因为有可能会提前返回
        *deleted = true;
        if (node->left == NULL) {
            BSTMapNode* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            BSTMapNode* temp = node->left;
            free(node);
            return temp;
        } else {
            // 左右子树都不为空，需要让右子树的最小节点替换掉当前节点
            BSTMapNode* succesor = bm_find_min(node->right);
            // 用最小节点的值替换当前节点的值
            node->key = succesor->key;
            node->value = succesor->value;
            // 把这个最小节点从右子树里删除
            node->right = bm_remove_node(node->right, succesor->key, deleted);
            // 左树不用管，因为没有任何影响
        }
    }
    return node;
}

void bm_remove(BSTMap* map, int key) {
    bool deleted = false;
    map->root = bm_remove_node(map->root, key, &deleted);
    if (deleted) {
        map->size--;
    }
}

int bm_size(BSTMap* map) {
    return map->size;
}

bool bm_contains(BSTMap* map, int key) {
    return bm_get_node(map->root, key) != NULL;
}

static void bm_print_node(BSTMapNode* node) {
    if (node != NULL) {
        bm_print_node(node->left);
        printf("%d: %d\n", node->key, node->value);
        bm_print_node(node->right);
    }
}

void bm_print(BSTMap* map) {
    printf("BSTMap size: %d\n", map->size);
    bm_print_node(map->root);
    printf("\n");
}