#include "bst.h"

#ifdef TEST_BST
int main() {
    BST* bst = bst_create();
    int arr[] = {5, 3, 6, 8, 4, 2};
    for (int i = 0; i < 6; i++) {
        bst_insert(bst, arr[i]);
    }
    bst_print(bst);
    printf("contains 4: %d\n", bst_contains(bst, 4));
    printf("contains 7: %d\n", bst_contains(bst, 7));
    bst_destroy(bst);
}
#endif
