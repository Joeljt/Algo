#include "linked_queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct LQNode {
    int data;
    struct LQNode* next;
} LQNode;

struct LinkedQueue {
    LQNode* head;
    LQNode* tail;
    int size;
};

LQNode* lq_createLNode(int data, LQNode* next) {
    LQNode* node = (LQNode*)malloc(sizeof(LQNode));
    if (node != NULL) {
        node->data = data;
        node->next = next;
        return node;
    }
    return NULL;
}

LinkedQueue* lq_create() {
    LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
        return queue;
    }
    return NULL;
}

void lq_destroy(LinkedQueue* queue) {
    if (queue != NULL) {
        LQNode* current = queue->head;
        while (current != NULL) {
            LQNode* next = current->next;
            free(current);
            current = next;
        }
        free(queue);
    }
}

void lq_enqueue(LinkedQueue* queue, int value) {
    if (queue != NULL) {
        if (queue->tail == NULL) {
            // 当前链表为空，新节点既是头节点也是尾节点
            queue->tail = lq_createLNode(value, NULL);
            queue->head = queue->tail;
        } else {
            // 当前链表不为空，新节点作为尾节点
            queue->tail->next = lq_createLNode(value, NULL);
            queue->tail = queue->tail->next;
        }
        queue->size++;
    }
}

int lq_dequeue(LinkedQueue* queue) {
    if (queue != NULL) {
        if (queue->head == NULL) {
            return -1;
        }
        LQNode* node = queue->head;
        int value = node->data;
        queue->head = queue->head->next;
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        free(node);
        queue->size--;
        return value;
    }
    return -1;
}

int lq_peek(LinkedQueue* queue) {
    if (lq_isEmpty(queue)) {
        return -1;
    }
    return queue->head->data;
} 

bool lq_isEmpty(LinkedQueue* queue) {
    return queue->size == 0;
}

void lq_print(LinkedQueue* queue) {
    printf("LQ: front [");
    for (LQNode* current = queue->head; current != NULL; current = current->next) {
        printf("%d->", current->data);
        if (current->next == NULL) {
            printf("NULL");
        }
    }
    printf("] tail\n");
}   