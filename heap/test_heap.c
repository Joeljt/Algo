#include <stdio.h>
#include "heap.h"

int main() {
  Heap* heap = createHeap(10);
  push(heap, 10);
  push(heap, 7);
  push(heap, 5);
  push(heap, 9);
  push(heap, 3);
  push(heap, 6);

  printf("peek: %d\n", peek(heap));

  push(heap, -1);
  printf("peek: %d\n", peek(heap));

  pop(heap);
  pop(heap);
  printf("peek: %d\n", peek(heap));

  destroyHeap(heap);
  return 0;
}
