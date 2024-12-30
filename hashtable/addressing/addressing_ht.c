#include "addressing_ht.h"

static size_t ah_hash(const char *key, size_t size) {
    size_t hash = 5381;  // DJB2 算法的初始值
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % size;
}

AddrHashTable *ah_create(size_t size) {
  AddrHashTable *hashtable = (AddrHashTable *)malloc(sizeof(AddrHashTable));
  hashtable->size = size;
  hashtable->count = 0;
  hashtable->data = (AddrHashNode **)malloc(size * sizeof(AddrHashNode*));
  for (size_t i = 0; i < size; i++) {
    hashtable->data[i] = NULL;
  }
  return hashtable;
}

void ah_destroy(AddrHashTable *hashtable) {
  // 回收哈希表中的所有节点
  for (size_t i = 0; i < hashtable->size; i++) {
    AddrHashNode *node = hashtable->data[i];
    if (node != NULL) {
      free(node->key);
      free(node);
      hashtable->data[i] = NULL;
      hashtable->count--;
    }
  }
  // 回收哈希表
  free(hashtable->data);
  free(hashtable);
}

void ah_put(AddrHashTable *hashtable, const char *key, void *value) {
  if (hashtable->count >= hashtable->size * LOAD_FACTOR) {
    // ah_resize(hashtable);
  }

  size_t index = ah_hash(key, hashtable->size);
  // 如果哈希表中已经存在该键，则更新其值
  AddrHashNode *node = hashtable->data[index];
  if (node != NULL && strcmp(node->key, key) == 0 && node->status == STATUS_USED) {
    node->value = value;
    return;
  }
  // 如果哈希表中不存在该键，则向后寻找空闲节点
  while (node != NULL && node->status == STATUS_USED) {
    index++;
    node = hashtable->data[index];
  }
  node = (AddrHashNode *)malloc(sizeof(AddrHashNode));
  node->key = strdup(key);
  node->value = value;
  node->status = STATUS_USED;
  hashtable->data[index] = node;
  hashtable->count++;
}

void* ah_get(AddrHashTable *hashtable, const char *key) {
  size_t index = ah_hash(key, hashtable->size);
  AddrHashNode *node = hashtable->data[index];
  if (node != NULL && strcmp(node->key, key) == 0 && node->status == STATUS_USED) {
    return node->value;
  } else {
    // 如果哈希表中不存在该键，则向后寻找
    while (node != NULL && node->status == STATUS_USED) {
      index++;
      node = hashtable->data[index];
    }
    // 如果找到的节点是空节点，则返回NULL
    if (node == NULL || node->status == STATUS_EMPTY || node->status == STATUS_DELETED) {
      return NULL;
    }
    return node->value;
  }
}

void ah_delete(AddrHashTable *hashtable, const char *key) {
  size_t index = ah_hash(key, hashtable->size);
  AddrHashNode *node = hashtable->data[index];
  if (node != NULL && strcmp(node->key, key) == 0 && node->status == STATUS_USED) {
    node->status = STATUS_DELETED;
    hashtable->count--;
  }
}

void ah_print(AddrHashTable *hashtable) {
  for (size_t i = 0; i < hashtable->size; i++) {
    if (hashtable->data[i] != NULL) {
      printf("%s: %s\n", hashtable->data[i]->key, (char*)hashtable->data[i]->value);
    }
  }
}