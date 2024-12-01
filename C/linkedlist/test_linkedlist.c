#include <stdio.h>
#include "linkedlist.h"

int main() {
  
  LinkedList* list = createList();

  for (int i = 0; i < 10; i++) {
    addLast(list, i);
    printList(list);
  }

  del(list, 3);
  delFirst(list);
  delLast(list);
  printList(list);

  set(list, 4, 777);
  set(list, 1, 999);
  printList(list);

  int e = get(list, 1);
  printf("target: %d\n", e);

  printf("Contains 7? %d", contains(list, 7));

  destroyList(list);

  return 0;
}