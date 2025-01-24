#include "ll_deque.h"

typedef struct DequeNode {
    int value;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

struct LinkedDeque {
    DequeNode *dummy;
    DequeNode *tail;
    int size;
};

LinkedDeque *ld_create() {
    LinkedDeque *deque = (LinkedDeque*)malloc(sizeof(LinkedDeque));
    deque->dummy = (DequeNode*)malloc(sizeof(DequeNode));
    deque->dummy->prev = NULL;
    deque->dummy->next = NULL;
    deque->tail = NULL;
    deque->size = 0;
    return deque;
}

void ld_destroy(LinkedDeque *deque) {
    DequeNode *current = deque->dummy->next;
    while (current != NULL) {
        DequeNode *next = current->next;
        free(current);
        current = next;
    }
    free(deque->dummy);
    free(deque);
}

void ld_push_back(LinkedDeque *deque, int value) {
    // 在尾部插入的节点，next 一定为 NULL，prev 指向原来的尾节点即可
    DequeNode *new_node = (DequeNode*)malloc(sizeof(DequeNode));
    new_node->value = value;
    new_node->next = NULL;

    // 检查链表是否为空，如果是空列表，直接插入到 dummy 后面即可
    if (deque->tail == NULL) {
        // 新节点的 prev 指向 dummy 节点
        new_node->prev = deque->dummy;
        // dummy 节点的 next 指向新节点
        deque->dummy->next = new_node;
    } else {
        // 链表不为空，把新节点插入到 tail 节点后面，整体步骤和上面类似
        new_node->prev = deque->tail;
        // 原来的尾节点的 next 指向新节点
        deque->tail->next = new_node;
    }

    // 让新节点成为新的尾节点
    deque->tail = new_node;
    // 链表长度加 1
    deque->size++;
}

int ld_pop_front(LinkedDeque *deque) {
    if (deque->tail == NULL) return -1;

    // 先把头节点保存起来
    DequeNode *head = deque->dummy->next;
    int value = head->value;

    // 如果只有这一个节点，就把 dummy 的 next 指向更新为 NULL，维护尾指针即可
    if (head->next == NULL) {
        deque->dummy->next = NULL;
        deque->tail = NULL;
    } else {
        // 否则，说明不止一个节点，就让 dummy 的指向跳过当前节点，把当前这个节点释放掉
        deque->dummy->next = head->next;
        // 不要忘记让新 head 节点的 prev 指向 dummy 节点
        head->next->prev = deque->dummy;
        // 当前节点的 prev 和 next 都没有用了，都断开指针链接
        head->prev = NULL;
        head->next = NULL;
    }

    // 释放掉当前节点
    free(head);
    // 链表长度减 1
    deque->size--;
    return value;
}

void ld_push_front(LinkedDeque *deque, int value) {
    DequeNode *new_node = (DequeNode*)malloc(sizeof(DequeNode));
    new_node->value = value; 

    // 在头部插入，新节点的 prev 一定是 dummy 节点
    new_node->prev = deque->dummy;

    // 如果队列为空，就直接插入到第一个位置，注意维护好新节点的指针关系
    if (deque->tail == NULL) {
        deque->dummy->next = new_node;
        new_node->next = NULL;
        // 维护尾指针
        deque->tail = new_node;
    } else {
        // 如果还有其他节点，直接操作 dummy 节点的指针关系完成插入即可
        // 而且不需要维护尾指针，因为在头部插入，不涉及尾指针的移动
        // 先把头节点取出来，让新节点的 next 指向原来的头节点，原来的头节点的 prev 指向新节点
        DequeNode* head = deque->dummy->next;
        new_node->next = head;
        head->prev = new_node;
        // 然后让 dummy 节点指向新节点，完成插入逻辑
        deque->dummy->next = new_node;
    }

    // 最后维护队列大小
    deque->size++;
}

int ld_pop_back(LinkedDeque *deque) {
    if (deque->tail == NULL) return -1;

    // 如果队列不为空，把尾节点取出来先保存
    DequeNode *target = deque->tail;
    int value = target->value;

    // 如果这是唯一一个节点
    if (target->prev == deque->dummy) {
        // 把和 dummy 节点的链接断开
        target->prev = NULL;
        // dummy 节点向后的链接也断开
        deque->dummy->next = NULL;
        // 清空尾节点的指向
        deque->tail = NULL;
    } else {
        // 让当前节点的前一个节点指向 NULL，成为新的尾节点
        target->prev->next = NULL;
        // 维护尾指针，指向当前节点的前一个节点
        deque->tail = target->prev;
        // 断开当前节点与前一个节点的链接
        target->prev = NULL;
    }

    free(target);
    deque->size--;
    return value;
}

int ld_peek_front(LinkedDeque *deque) {
    if (deque->dummy->next == NULL) return -1;
    return deque->dummy->next->value;
}

int ld_peek_back(LinkedDeque *deque) {
    if (deque->tail == NULL) return -1;
    return deque->tail->value;
}

void ld_print(LinkedDeque *deque) {
    DequeNode *current = deque->dummy->next;
    printf("LinkedDeque: front [");
    while (current != NULL) {
        printf("%d->", current->value);
        current = current->next;
    }
    printf("NULL] tail\n");
}