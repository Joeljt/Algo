#include "chaining_ht.h"

#define LOAD_FACTOR 0.75

typedef struct ChainingHashNode {
  char *key;
  void *value;
  struct ChainingHashNode* next;
} ChainingHashNode;

struct ChainingHashTable {
    size_t size;
    size_t count;
    // hash 表的底层数据结构实际上是数组，被称为哈希桶
    // 数组中的每个元素都是一个链表，链表中的每个节点都是一个键值对
    ChainingHashNode** buckets; 
};

static size_t chht_hash(const char *key, size_t size) {
  size_t hash = 0;
  for (size_t i = 0; key[i] != '\0'; i++) {
    hash = (hash * 31 + key[i]) % 1000000007;
  }
  return hash & (size - 1);
}

// static size_t chht_hash_djb2(const char *key, size_t size) {
//     size_t hash = 5381;  // DJB2 算法的初始值
//     int c;
//     while ((c = *key++)) {
//         hash = ((hash << 5) + hash) + c;  // hash * 33 + c
//     }
//     return hash & (size - 1);
// }

ChainingHashTable *chht_create() {
  // 分配哈希表结构体
  ChainingHashTable *hashtable = (ChainingHashTable *)malloc(sizeof(ChainingHashTable));
  // 初始化基本数据
  hashtable->size = 2 << 3; // 2^3 = 8
  hashtable->count = 0;

  // 分配桶数组，每个数组元素都是一个链表，需要使用二级指针，
  // 因为数组元素是 ChainingHashNode* 类型，而 ChainingHashNode 本身是一个结构体
  // 第二个 * 表示当前 buckets 是数组
  hashtable->buckets = (ChainingHashNode **)malloc(hashtable->size * sizeof(ChainingHashNode*));
  // 初始化哈希桶的数组，每个元素都是一个链表
  for (size_t i = 0; i < hashtable->size; i++) {
    hashtable->buckets[i] = NULL;
  }

  return hashtable;
}

void chht_destroy(ChainingHashTable *hashtable) {
  // 遍历哈希表，释放桶中所有节点
  for (size_t i = 0; i < hashtable->size; i++) {
    ChainingHashNode* current = hashtable->buckets[i];
    while (current != NULL) {
      ChainingHashNode* next = current->next;
      free(current->key);
      // free(current->value);
      free(current);
      current = next;
    }
  }
  // 释放桶数组
  free(hashtable->buckets);
  // 释放哈希表结构
  free(hashtable);
}

void chht_resize(ChainingHashTable *hashtable, size_t new_size) {
  // 用新的大小重新申请内存，并初始化空桶
  ChainingHashNode **new_buckets = (ChainingHashNode **)malloc(new_size * sizeof(ChainingHashNode*));
  for (size_t i = 0; i < new_size; i++) {
    new_buckets[i] = NULL;
  }
  // 将旧桶中的元素重新分配到新桶中
  for (size_t i = 0; i < hashtable->size; i++) {
    ChainingHashNode *current = hashtable->buckets[i];
    while (current != NULL) {
        // 保存下一个节点，因为我们要修改 current->next
        ChainingHashNode *next = current->next;
        
        // 重新计算 hash 值，并插入到新桶中
        size_t new_index = chht_hash(current->key, new_size);
        // 将当前节点插入到新桶的链表头部
        current->next = new_buckets[new_index];
        new_buckets[new_index] = current;
        
        // 移动到下一个节点
        current = next;
    }
  }
  // 释放旧桶
  free(hashtable->buckets);
  // 更新桶数组
  hashtable->buckets = new_buckets;
  // 更新哈希表大小
  hashtable->size = new_size;
}

void chht_put(ChainingHashTable *hashtable, const char *key, void *value) {
  if (hashtable->count >= hashtable->size * LOAD_FACTOR) {
    chht_resize(hashtable, hashtable->size * 2);
  }

  size_t index = chht_hash(key, hashtable->size);

  // 检查是否是重复节点，如果是，则更新 value
  ChainingHashNode *current = hashtable->buckets[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      current->value = value;
      return;
    }
    current = current->next;
  }

  // 如果不存在，就创建新节点，并插入到链表尾部
  ChainingHashNode *new_node = (ChainingHashNode*)malloc(sizeof(ChainingHashNode));
  new_node->key = strdup(key);
  new_node->value = value;

  // 将新节点插入到链表头部
  // 不能插入到尾部，是因为上面遍历完以后，current 指向 NULL
  new_node->next = hashtable->buckets[index];
  hashtable->buckets[index] = new_node;

  // 维护哈希表的元素数量
  hashtable->count++;
}

void* chht_get(ChainingHashTable *hashtable, const char *key) {
  size_t index = chht_hash(key, hashtable->size);
  ChainingHashNode *node = hashtable->buckets[index];
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->value;
    }
    node = node->next;
  }
  return NULL;
}

void chht_delete(ChainingHashTable *hashtable, const char *key) {
  size_t index = chht_hash(key, hashtable->size);
  ChainingHashNode *node = hashtable->buckets[index];
  ChainingHashNode *prev = NULL;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      if (prev == NULL) {
        hashtable->buckets[index] = node->next;
      } else {
        prev->next = node->next;
      }
      free(node);
      hashtable->count--;
      break;
    }
    prev = node;
    node = node->next;
  }
  // 如果元素数量小于哈希表大小的 1/4，则缩小哈希表
  if (hashtable->count < hashtable->size / 4 && hashtable->size / 2 >= 8) {
    chht_resize(hashtable, hashtable->size / 2);
  }
}

void chht_print(ChainingHashTable *hashtable) {
  printf("HashTable size: %zu, count: %zu\n", hashtable->size, hashtable->count);
  for (size_t i = 0; i < hashtable->size; i++) {
    ChainingHashNode *node = hashtable->buckets[i];
    if (node != NULL) {
      printf("Bucket %zu: ", i);
      while (node != NULL) {
        printf("%s -> ", node->key);
        node = node->next;
      }
      printf("NULL\n");
    }
  }
  printf("\n");
} 
