#include <stdio.h>
#include "single/linkedlist.h"

#ifdef TEST_LINKEDLIST
int main() {
  
  LinkedList* list = ll_create();

  for (int i = 0; i < 10; i++) {
    ll_addLast(list, i);
    ll_printList(list);
  }

  ll_del(list, 3);
  ll_delFirst(list);
  ll_delLast(list);
  ll_printList(list);

  ll_set(list, 4, 777);
  ll_set(list, 1, 999);
  ll_printList(list);

  int e = ll_get(list, 1);
  printf("target: %d\n", e);

  printf("Contains 7? %d", ll_contains(list, 7));

  ll_destroy(list);

  return 0;
}
#endif