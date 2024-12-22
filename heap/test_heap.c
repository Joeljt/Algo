#include <stdio.h>
#include "basic/heap.h"
#include "index/index_heap.h"
#ifdef TEST_HEAP

void test_heap() {
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
}

void test_index_heap() {
  IndexHeap* heap = ih_create(5);
  for (int i = 0; i < 10; i++) {
    ih_push(heap, i);
    ih_print(heap);  
  }

  ih_pop(heap);
  ih_pop(heap);
  ih_print(heap);

  ih_update(heap, 3, 13);
  ih_print(heap);

  ih_destroy(heap);
}

int main() {
  test_heap();
  printf("\n");
  test_index_heap();
  return 0;
}
#endif