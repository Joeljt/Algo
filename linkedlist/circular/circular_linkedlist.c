#include "circular_linkedlist.h"

typedef struct CNode {
    int value;
    struct CNode *next;
} CNode;

struct CircularLinkedList {
    CNode *last;
    int size;
};

CircularLinkedList* cl_create() {
    CircularLinkedList *list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    list->last = NULL;
    list->size = 0;
    return list;
}

void cl_destroy(CircularLinkedList *list) {
    assert(list != NULL);
    assert(list->size > 0);

    // 把环断开
    CNode *head = list->last->next;
    list->last->next = NULL;

    // 从当前节点开始遍历
    CNode *current = head;
    CNode *next;
    // 如果链表为空，当前节点就是 NULL
    while (current != NULL) {
        // 拿到下一个节点，先保存下来
        next = current->next;
        // 释放当前节点
        free(current);
        // 将当前节点指向下一个节点后继续遍历
        // 直到遍历一圈后，current 会指向 NULL
        current = next;
    }
    // 释放所有节点后，释放链表
    free(list);
}

void cl_add(CircularLinkedList *list, int value, int index) {
    assert(list != NULL);
    assert(index >= 0 && index <= list->size);

    CNode *node = (CNode*)malloc(sizeof(CNode));
    node->value = value;

    // 如果当前链表为空，则直接将新节点作为头节点
    // 这两个条件是等价的，因为链表为空时，last 为 NULL 并且 size 为 0
    if (list->last == NULL || list->size == 0) {
        list->last = node;
        node->next = node; // 指向自己，形成空环
    } 
    // last 是最后一个节点，所以 last->next 是第一个节点
    // 在头部插入
    // 注意，在头部插入后，不需要维护 last 指针
    //因为 last 原本指向的节点，在完成本次插入后仍然是最后一个节点
    else if (index == 0) {
        node->next = list->last->next; // 新节点指向第一个节点
        list->last->next = node; // 最后一个节点指向新节点
    }
    // 在尾部插入
    else if (index == list->size) {
        node->next = list->last->next;
        list->last->next = node;
        list->last = node; // 在尾部插入后，需要维护 last 指向新节点
    }
    // 在中间某个位置插入，与单链表的插入操作一致
    // 找到插入位置的前一个节点，然后插入
    else {
        CNode *prev = list->last;
        for (int i = 0; i < index; i++) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
    }
    list->size++;
}

int cl_remove(CircularLinkedList *list, int index) {
    assert(list != NULL);
    assert(list->size > 0);
    assert(index >= 0 && index < list->size);

    // last 就是链表尾，也就是链表头的前一个节点
    // 从头开始遍历，找到要删除的节点的前一个节点
    CNode *prev = list->last;
    for (int i = 0; i < index; i++) {
        prev = prev->next;
    }
    // 取出要删除的节点
    CNode *target = prev->next;
    int value = target->value;

    // 如果当前只有这一个节点，则直接删除，然后更新 last 指针为 NULL
    if (target == target->next || list->size == 1) {
        list->last = NULL;
    } else {
        // 跳过要删除的节点，让前一个节点指向后一个节点
        prev->next = target->next;
        // 如果删除的是最后一个节点，则需要维护 last 指针
        if (target == list->last) {
            list->last = prev;
        }
    }

    free(target);
    list->size--;
    return value;
}

int cl_get(CircularLinkedList *list, int index) {
    assert(list != NULL);
    assert(list->size > 0);
    assert(index >= 0 && index < list->size);

    CNode *current = list->last;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

void cl_print(CircularLinkedList *list) {
    assert(list != NULL);

    CNode *current = list->last;
    if (current == NULL) {
        printf("[empty]\n");
        return;
    }   

    // 先移动到第一个节点
    current = current->next;
    printf("[HEAD->");
    
    // 打印一整圈
    do {
        printf("%d->", current->value);
        current = current->next;
    } while (current != list->last->next);
    
    // 显示回到开头，体现循环特性
    printf("HEAD]\n");
}