#ifndef BST_MAP_H
#define BST_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct BSTMap BSTMap;

BSTMap* bm_create();
void bm_destroy(BSTMap* map);

void bm_put(BSTMap* map, int key, int value);
int bm_get(BSTMap* map, int key, int fallback);
void bm_remove(BSTMap* map, int key);

bool bm_contains(BSTMap* map, int key);
int bm_size(BSTMap* map);

void bm_print(BSTMap* map);

#endif
