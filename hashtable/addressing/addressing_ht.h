#ifndef ADDRESSING_HT_H
#define ADDRESSING_HT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 0.5
#define STATUS_EMPTY 0
#define STATUS_USED 1
#define STATUS_DELETED 2

typedef struct AddrHashNode {
  char *key;
  void *value;
  int status;
} AddrHashNode;

typedef struct AddrHashTable {
  size_t size;
  size_t count;
  AddrHashNode **data;
} AddrHashTable;

AddrHashTable *ah_create(size_t size);
void ah_destroy(AddrHashTable *hashtable);

void ah_put(AddrHashTable *hashtable, const char *key, void *value);
void *ah_get(AddrHashTable *hashtable, const char *key);
void ah_delete(AddrHashTable *hashtable, const char *key);

void ah_print(AddrHashTable *hashtable);

#endif