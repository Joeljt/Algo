#include "trie.h"

struct TrieNode {
    bool is_word;
    TrieNode* children[26];
};

struct Trie {
    TrieNode* root;
    int size;
};

TrieNode* trie_node_create() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_word = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

Trie* trie_create() {
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = trie_node_create();
    trie->size = 0;
    return trie;
}

void trie_destroy_node(TrieNode* node) {
    if (node != NULL) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != NULL) {
                trie_destroy_node(node->children[i]);
            }
        }
        free(node);
    }
}

void trie_destroy(Trie* trie) {
    if (trie != NULL) {
        trie_destroy_node(trie->root);
        free(trie);
    }
}

void trie_insert(Trie* trie, const char* word) {
    TrieNode* cur = trie->root;
    // 遍历传入的单词，C 没有字符串，只是 char 数组
    // 按索引访问即可，直到遇到字符串 null 标记符 \0
    for (int i = 0; word[i] != '\0'; i++) {
        // Trie 的节点不需要存储字母信息，而是用下标隐含了字母信息
        // 对每个字母进行 'a' 的偏移，保证 a-z 能对应上 0-25 的下标
        int index = word[i] - 'a';

        // 之后看一下当前节点对应的字母是不是有值，没有的话就在对应的位置创建一个新节点
        // 然后循环继续向下，直到走完整个单词
        if (cur->children[index] == NULL) {
            cur->children[index] = trie_node_create();
        }

        // 更新 cur 节点为当前 index 的节点，也就是遍历到的这个字母
        cur = cur->children[index];
    }
    // 执行到这里，cur 就指向了最后一个字母的节点，需要标记这里是个单词
    // 同时需要判断一下当前是不是已经加过这个单词了，第一次添加才维护 size
    if (!cur->is_word) {
        cur->is_word = true;
        trie->size++;
    }
}

bool trie_find(Trie* trie, const char* word) {
    TrieNode* cur = trie->root; 
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (cur->children[index] != NULL) {
            cur = cur->children[index];
        } else {
            // 在没有遍历到单词末尾的时候，就遇到了空节点，说明树里没有这个单词
            return false;
        }
    }
    // 最后找到这个单词了，但还要判断一下是不是添加过
    // 因为有可能是其他单词的前缀
    return cur->is_word;
}

bool trie_start_with(Trie* trie, const char* prefix) {
    TrieNode* cur = trie->root;
    for (int i = 0; prefix[i] != '\0'; i++) {
       int index = prefix[i] - 'a';
       if (cur->children[index] != NULL) {
            cur = cur->children[index];
       } else {
            return false;
       } 
    }
    return true;
}

int trie_size(Trie* trie) {
    return trie->size;
}

void trie_print(Trie* trie) {
    printf("%d\n", trie->size);
}