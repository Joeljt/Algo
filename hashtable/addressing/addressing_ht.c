#include "addressing_ht.h"

AddrHashTable *ah_create(size_t size) {
  AddrHashTable *hashtable = (AddrHashTable *)malloc(sizeof(AddrHashTable));
  hashtable->size = size;
  hashtable->count = 0;
  hashtable->data = (AddrHashNode *)malloc(size * sizeof(AddrHashNode));
  for (size_t i = 0; i < size; i++) {
    hashtable->data[i].status = STATUS_EMPTY;
  }
  return hashtable;
}
