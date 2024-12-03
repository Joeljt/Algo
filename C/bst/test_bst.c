#include "bst.h"

int main() {
    BST* bst = createBST();
    int arr[] = {5, 3, 6, 8, 4, 2};
    for (int i = 0; i < 6; i++) {
        insert(bst, arr[i]);
    }
    print(bst);
    destroyBST(bst);
}
