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

bool is_empty_node(TrieNode* node) {
    if (node == NULL) return true;
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            // 只要有一个子节点不为空，就说明不是空树
            return false;
        }
    }
    // 所有子节点都为空
    return true;
}

bool trie_delete(Trie* trie, TrieNode* node, const char* word, int depth) {
    if (node == NULL) return false;

    // 检查当前是否递归到单词末尾了
    if (word[depth] == '\0') {
        // 如果当前位置确实存了单词，就取消标记，逻辑删除
        if (node->is_word) {
            node->is_word = false;
            trie->size--;
            // 然后检查当前节点是否还有其他子节点
            // 只有 26 个子节点都为空，当前节点才能被删除，说明没有其他单词在使用这个字母
            return is_empty_node(node);
        }
        // 当前单词在字典树中不存在，不可以删除
        return false;
    }

    // 否则就继续递归向下，depth++，递归删除子节点
    int index = word[depth] - 'a';
    if (trie_delete(trie, node->children[index], word, depth + 1)) {
        // 如果下层子节点可以被删除，直接释放节点空间
        free(node->children[index]);
        // 清空指针
        node->children[index] = NULL;

        // 如果当前节点不是【其他单词】的末尾字母，并且也没有子节点，就可以删除
        return !node->is_word && is_empty_node(node);
    }

    // 执行到这里，说明 trie_is_removable 返回 false
    // 1. 表示在当前节点的子节点中没有找到要删除的单词
    // 2. 当前节点的子节点不需要被删除，仍然有其他单词共享该子节点
    return false;
}

void trie_remove(Trie* trie, const char* word) {
    trie_delete(trie, trie->root, word, 0);
}

int trie_size(Trie* trie) {
    return trie->size;
}

void trie_print(Trie* trie) {
    printf("%d\n", trie->size);
}
