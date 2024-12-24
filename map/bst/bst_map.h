#ifndef BST_MAP_H
#define BST_MAP_H

#include "../../bst/bst.h"

typedef struct BSTMap BSTMap;

BSTMap* bm_create();
void bm_destroy(BSTMap* map);

void bm_put(BSTMap* map, int key, int value);
int bm_get(BSTMap* map, int key);
void bm_remove(BSTMap* map, int key);

void bm_print(BSTMap* map);

#endif
