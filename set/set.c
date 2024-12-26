#include "set.h"

MapSet *ms_create() {
    MapSet *set = (MapSet *)malloc(sizeof(MapSet));
    set->map = bm_create();
    return set;
}

void ms_destroy(MapSet *set) {
    bm_destroy(set->map);
    free(set);
}

void ms_add(MapSet *set, int key) {
    bm_put(set->map, key, 0);
}

void ms_remove(MapSet *set, int key) {
    bm_remove(set->map, key);
}

bool ms_contains(MapSet *set, int key) {
    return bm_contains(set->map, key);
}

int ms_size(MapSet *set) {
    return bm_size(set->map);
}

void ms_print(MapSet *set) {
    printf("Set: ");
    bm_print(set->map);
}
