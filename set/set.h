#ifndef SET_H
#define SET_H

#include "map/bst/bst_map.h"

typedef struct MapSet {
    BSTMap *map;
} MapSet;

MapSet *ms_create();
void ms_destroy(MapSet *set);

void ms_add(MapSet *set, int key);
void ms_remove(MapSet *set, int key);

bool ms_contains(MapSet *set, int key);
int ms_size(MapSet *set);

void ms_print(MapSet *set);

#endif