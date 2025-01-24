#include "sf_linkedlist.h"
#include <stdio.h>

// int main() {

    // 每次都在最开始插入，导致最终结果是倒序
    // 4 -> 3 -> 2 -> 1 -> NULL
    // Node* head = NULL;
    // addLast(&head, 4);
    // addLastTheHardWay(&head, 5);
    // addFirst(&head, 1);
    // addFirst(&head, 2);
    // addFirst(&head, 3);
    // addLast(&head, 6);
    // addLastTheHardWay(&head, 7);
    // printLinkedList(head);
    
    // /// =========================
    // Node *list = buildOneTwoThree();
    // printLinkedList(list);

    // /// =========================
    // Node* list2 = buildWithSpecialCase();
    // printLinkedList(list2);

    // /// =========================
    // Node* list3 = buildWithDummyHead();
    // printLinkedList(list3);
    
    // /// =========================
    // Node* list4 = buildWithLocalReference();
    // printLinkedList(list4);

//     return 0;
// }