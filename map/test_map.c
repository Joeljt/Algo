#include "bst/bst_map.h"

#ifdef TEST_BST_MAP

void test_bst_map() {
    BSTMap* map = bm_create();
    bm_put(map, 1, 1);
    bm_put(map, 2, 2);
    bm_put(map, 3, 3);
    bm_print(map);
    bm_destroy(map);
}

int main() {
    test_bst_map();
}
#endif
