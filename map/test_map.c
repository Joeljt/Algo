#include "bst/bst_map.h"

#ifdef TEST_MAP

void test_bst_map() {
    BSTMap* map = bm_create();
    bm_put(map, 1, 1);
    bm_put(map, 2, 2);
    bm_put(map, 3, 3);
    bm_print(map);

    bm_remove(map, 2);
    bm_print(map);

    bm_put(map, 12, 19);
    bm_print(map);
    printf("contains 4: %d\n", bm_contains(map, 4));
    printf("get 12: %d\n", bm_get(map, 12, -1));

    bm_destroy(map);
}

int main() {
    test_bst_map();
    return 0;
}
#endif
