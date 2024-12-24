#include "bst_map.h"

struct BSTMap {
    BST* bst;
};

BSTMap* bm_create() {
    BSTMap* map = (BSTMap*)malloc(sizeof(BSTMap));
    map->bst = bst_create();
    return map;
}

void bm_destroy(BSTMap* map) {
    bst_destroy(map->bst);
    free(map);
}

void bm_put(BSTMap* map, int key, int value) {
    bst_insert(map->bst, key);
}

int bm_get(BSTMap* map, int key) {
    return bst_contains(map->bst, key);
}

void bm_remove(BSTMap* map, int key) {
    bst_delete(map->bst, key);
}

void bm_print(BSTMap* map) {
    bst_print(map->bst);
}