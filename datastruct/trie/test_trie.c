#include "trie.h"

#ifdef TEST_TRIE
int main() {
    Trie* trie = trie_create();
    trie_insert(trie, "cat");
    trie_insert(trie, "car");
    printf("Size before delete: %d\n", trie_size(trie)); // 应该是2
    trie_remove(trie, "cat");
    printf("Size after delete: %d\n", trie_size(trie)); // 应该是1
    trie_remove(trie, "dog"); // 尝试删除不存在的单词
    printf("Size after trying to delete non-existent word: %d\n", trie_size(trie)); // 应该仍然是1

    trie_destroy(trie);
    return 0;
}
#endif