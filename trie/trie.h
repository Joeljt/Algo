#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TrieNode TrieNode;
typedef struct Trie Trie;

Trie* trie_create();
void trie_destroy(Trie* trie);

void trie_insert(Trie* trie, const char* word);
bool trie_find(Trie* trie, const char* word);
bool trie_start_with(Trie* trie, const char* prefix);
// void trie_remove(Trie* trie, const char* word);

int trie_size(Trie* trie);

void trie_print(Trie* trie);

#endif
