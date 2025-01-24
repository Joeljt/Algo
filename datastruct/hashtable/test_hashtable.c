#include "chaining/chaining_ht.h"
#include "addressing/addressing_ht.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef TEST_HASHTABLE

char* generate_key(const char* base, int i) {
    // 分配足够的内存来存储结果字符串
    size_t length = snprintf(NULL, 0, "%s%d", base, i) + 1; // 计算需要的长度
    char* result = (char*)malloc(length); // 动态分配内存
    if (result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    snprintf(result, length, "%s%d", base, i); // 格式化字符串
    return result;
}

void test_chaining_ht() {
  ChainingHashTable *hashtable = chht_create();

  chht_put(hashtable, "key1", "value1");
  chht_put(hashtable, "key4", "value4");
  chht_put(hashtable, "key5", "value5");
  chht_put(hashtable, "key9", "value9");
  
  printf("-----------------------------------\n");

  printf("get key4: %s\n", (char*)chht_get(hashtable, "key4"));
  int value4 = 1219;
  chht_put(hashtable, "key4", &value4);
  printf("get key4: %d\n", *(int*)chht_get(hashtable, "key4"));
  chht_delete(hashtable, "key4");
  printf("get key4: %s\n", (char*)chht_get(hashtable, "key4"));

  printf("-----------------------------------\n");

  chht_put(hashtable, "Aa", "测试哈希冲突");
  chht_put(hashtable, "BB", "测试哈希冲突");
  chht_put(hashtable, "Cc", "测试哈希冲突");
  chht_put(hashtable, "DD", "测试哈希冲突");
  chht_put(hashtable, "Ee", "测试哈希冲突");
  chht_print(hashtable);

  chht_destroy(hashtable);
}

void test_addressing_ht() {
  AddrHashTable *hashtable = ah_create(5);
  ah_put(hashtable, "key1", "value1");
  ah_put(hashtable, "key4", "value4");
  ah_put(hashtable, "key5", "value5");
  ah_put(hashtable, "key6", "value6");
  ah_put(hashtable, "key7", "value7");
  ah_print(hashtable);

  printf("-----------------------------------\n");

  printf("get key4: %s\n", (char*)ah_get(hashtable, "key4"));
  int value4 = 1219;
  ah_put(hashtable, "key4", &value4);
  printf("get key4: %d\n", *(int*)ah_get(hashtable, "key4"));
  ah_delete(hashtable, "key4");
  printf("get key4: %s\n", (char*)ah_get(hashtable, "key4"));

  printf("-----------------------------------\n");

  ah_put(hashtable, "Aa", "测试哈希冲突");
  ah_put(hashtable, "BB", "测试哈希冲突");
  ah_put(hashtable, "Cc", "测试哈希冲突");
  ah_print(hashtable);

  ah_destroy(hashtable);
}

int main() {
  test_chaining_ht();
  test_addressing_ht();
  return 0;
}
#endif