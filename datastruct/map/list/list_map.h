#ifndef LIST_MAP_H
#define LIST_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ListMapNode {
  int key;
  int value;
  struct ListMapNode *next;
} ListMapNode;

typedef struct ListMap {
  ListMapNode *dummy;
  int size;
} ListMap;

ListMap *lm_create();
void lm_destroy(ListMap *map);

void lm_put(ListMap *map, int key, int value);
int lm_get(ListMap *map, int key, int default_value);
void lm_remove(ListMap *map, int key);

bool lm_contains(ListMap *map, int key);
int lm_size(ListMap *map);

void lm_print(ListMap *map);

#endif
