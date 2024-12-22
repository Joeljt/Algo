#include <stdio.h>
#include "heap.h"

#ifdef TEST_HEAP
int main() {
  Heap* heap = heap_create(5);

  for (int i = 0; i < 10; i++) {
    heap_push(heap, i);
    heap_print(heap);  
  }

  heap_push(heap, 13);
  heap_print(heap);

  heap_pop(heap);
  heap_print(heap);

  heap_pop(heap);
  heap_print(heap);

  heap_destroy(heap);
  return 0;
}
#endif