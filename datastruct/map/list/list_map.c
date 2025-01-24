#include "list_map.h"

ListMap *lm_create() {
  ListMap *map = (ListMap *)malloc(sizeof(ListMap));
  map->dummy = (ListMapNode *)malloc(sizeof(ListMapNode));
  map->dummy->next = NULL;
  map->size = 0;
  return map;
}

void lm_destroy(ListMap *map) {
  ListMapNode *current = map->dummy;
  while (current != NULL) {
    ListMapNode *next = current->next;
    free(current);
    current = next;
  }
  free(map);
}

void lm_put(ListMap *map, int key, int value) {
  ListMapNode *current = map->dummy;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = (ListMapNode *)malloc(sizeof(ListMapNode));
  current->next->key = key;
  current->next->value = value;
  current->next->next = NULL;
  map->size++;
}

int lm_get(ListMap *map, int key, int default_value) {
  ListMapNode *current = map->dummy;
  while (current->next != NULL) {
    current = current->next;
    if (current->key == key) {
      return current->value;
    }
  }
  return default_value;
}

void lm_remove(ListMap *map, int key) {
  ListMapNode *current = map->dummy;
  while (current->next != NULL) {
    if (current->next->key == key) {
      ListMapNode *next = current->next->next;
      free(current->next);
      current->next = next;
      map->size--;
      return;
    }
    current = current->next;
  }
}

bool lm_contains(ListMap *map, int key) {
  return lm_get(map, key, -1) != -1;
}

int lm_size(ListMap *map) {
  return map->size;
}

void lm_print(ListMap *map) {
  ListMapNode *current = map->dummy;
  while (current->next != NULL) {
    current = current->next;
    printf("(%d, %d) ", current->key, current->value);
  }
  printf("\n");
}
