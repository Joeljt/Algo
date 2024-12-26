#include "set.h"

void test_set() {
    MapSet *set = ms_create();
    ms_add(set, 1);
    ms_add(set, 1);
    ms_add(set, 2);
    ms_add(set, 3);
    ms_add(set, 3);
    ms_add(set, 4);
    
    printf("size: %d\n", ms_size(set));
    printf("contains 1: %d\n", ms_contains(set, 1));
    printf("contains 5: %d\n", ms_contains(set, 5));

    ms_destroy(set);
}

#ifdef TEST_SET
int main() {
    test_set();
    return 0;
}
#endif