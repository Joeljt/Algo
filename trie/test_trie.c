#include "trie.h"

#ifdef TEST_TRIE
int main() {
    Trie* trie = trie_create();
    
    trie_insert(trie, "panda");
    trie_insert(trie, "peacock");
    trie_insert(trie, "pan");

    trie_print(trie);

    printf("contains 'pan': %d\n", trie_find(trie, "pan"));
    printf("start with 'pan': %d\n", trie_start_with(trie, "panda"));

    trie_destroy(trie);
    return 0;
}
#endif