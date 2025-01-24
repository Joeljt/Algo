#ifndef _CHAINING_HT_H_
#define _CHAINING_HT_H_

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ChainingHashTable ChainingHashTable;

ChainingHashTable *chht_create();
void chht_destroy(ChainingHashTable *hashtable);

void chht_put(ChainingHashTable *hashtable, const char *key, void *value);
void* chht_get(ChainingHashTable *hashtable, const char *key);
void chht_delete(ChainingHashTable *hashtable, const char *key);

void chht_print(ChainingHashTable *hashtable);

#endif
