#include <stdio.h>
#include "single/linkedlist.h"
#include "double/double_linkedlist.h"

#ifdef TEST_LINKEDLIST

void test_single_linkedlist() {
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
}

void test_double_linkedlist() {
  DoubleLinkedList* list = dl_create();

  for (int i = 0; i < 10; i++) {
    dl_add(list, i, i);
    dl_print(list);
  }

  dl_remove(list, 3);
  dl_print(list);

  dl_set(list, 4, 777);
  dl_set(list, 1, 999);
  dl_print(list);

  dl_destroy(list);
}

int main() {
  test_single_linkedlist();
  printf("\n\n");
  test_double_linkedlist();
  return 0;
}
#endif