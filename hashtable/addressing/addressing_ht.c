#include "addressing_ht.h"

static size_t ah_hash(const char *key, size_t size) {
    size_t hash = 5381;  // DJB2 算法的初始值
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % size;
}

static void ah_resize(AddrHashTable *hashtable, size_t new_size) {
    // 保存旧数据
    AddrHashNode **old_data = hashtable->data;
    size_t old_size = hashtable->size;
    
    // 创建新数组
    hashtable->data = (AddrHashNode **)malloc(new_size * sizeof(AddrHashNode*));
    hashtable->size = new_size;
    hashtable->count = 0;
    
    // 初始化新数组
    for (size_t i = 0; i < new_size; i++) {
        hashtable->data[i] = NULL;
    }
    
    // 重新插入所有有效的节点
    for (size_t i = 0; i < old_size; i++) {
        AddrHashNode *node = old_data[i];
        if (node != NULL && node->status == STATUS_USED) {
            // 重新插入节点
            size_t index = ah_hash(node->key, new_size);
            // 线性探测找到新的空位置
            while (hashtable->data[index] != NULL) {
                index = (index + 1) % new_size;
            }
            hashtable->data[index] = node;
            hashtable->count++;
        } else if (node != NULL) {
            // 释放已删除或空节点的内存
            free(node->key);
            free(node);
        }
    }
    
    // 释放旧数组（只释放数组本身，不释放节点）
    free(old_data);
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
    // 检查是否需要扩容
    // 线性探测的负载因子不能超过 1，并且也不能太大，否则性能就会下降
    if (hashtable->count >= hashtable->size * LOAD_FACTOR) {
        ah_resize(hashtable, hashtable->size * 2);
    }

    size_t index = ah_hash(key, hashtable->size);
    // 因为 index 是随机的，所以线性探测的时候需要考虑下标循环的问题
    size_t original_index = index;
    
    do {
        AddrHashNode *node = hashtable->data[index];
        
        // 如果找到空位置或已删除的位置
        // 这里可以对已删除的节点进行复用，减少内存分配
        if (node == NULL || node->status != STATUS_USED) {
            node = (AddrHashNode *)malloc(sizeof(AddrHashNode));
            node->key = strdup(key);
            node->value = value;
            node->status = STATUS_USED;
            hashtable->data[index] = node;
            hashtable->count++;
            return;
        }
        
        // 如果找到相同的键，更新值
        if (strcmp(node->key, key) == 0 && node->status == STATUS_USED) {
            node->value = value;
            return;
        }
        
        // 线性探测下一个位置
        // 下标循环
        index = (index + 1) % hashtable->size;
    } while (index != original_index);
    
    // 如果表已满（不应该发生，因为我们有负载因子控制）
    // 为了安全起见，在这里进行扩容并重试
    ah_resize(hashtable, hashtable->size * 2);
    ah_put(hashtable, key, value);
}

void* ah_get(AddrHashTable *hashtable, const char *key) {
    size_t index = ah_hash(key, hashtable->size);
    size_t original_index = index;  // 记录初始位置
    
    do {
        AddrHashNode *node = hashtable->data[index];
        
        // 如果找到匹配的键且状态为已使用
        if (node != NULL && node->status == STATUS_USED && strcmp(node->key, key) == 0) {
            return node->value;
        }
        
        // 如果遇到空节点，说明键不存在
        if (node == NULL || node->status == STATUS_EMPTY) {
            return NULL;
        }
        
        // 线性探测下一个位置
        index = (index + 1) % hashtable->size;
    } while (index != original_index);  // 直到回到起始位置
    
    // 如果遍历了整个表都没找到，返回NULL
    return NULL;
}

void ah_delete(AddrHashTable *hashtable, const char *key) {
  size_t index = ah_hash(key, hashtable->size);
  AddrHashNode *node = hashtable->data[index];
  if (node != NULL && strcmp(node->key, key) == 0 && node->status == STATUS_USED) {
    node->status = STATUS_DELETED;
    hashtable->count--;
    if (hashtable->count < hashtable->size / 4 && hashtable->size / 2 >= 8) {
      ah_resize(hashtable, hashtable->size / 2);
    }
  }
}

void ah_print(AddrHashTable *hashtable) {
  printf("Addressing HashTable size: %zu, count: %zu\n", hashtable->size, hashtable->count);
  for (size_t i = 0; i < hashtable->size; i++) {
    AddrHashNode *node = hashtable->data[i];
    if (node != NULL) {
      printf("Bucket %zu: ", i);
      printf("%s\n", node->key);
    }
  }
  printf("\n");
} 