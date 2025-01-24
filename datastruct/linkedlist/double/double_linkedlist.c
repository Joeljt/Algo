#include "double_linkedlist.h"
#include "assert.h"
#include <stdio.h>

struct DNode {
    int value;
    DNode* prev;
    DNode* next;
};

struct DoubleLinkedList {
    DNode* dummy;
    int size;
};

DoubleLinkedList* dl_create() {
    DoubleLinkedList* list = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    DNode* dummy = (DNode*)malloc(sizeof(DNode));
    dummy->value = -1;
    dummy->prev = NULL;
    dummy->next = NULL;
    list->dummy = dummy;
    list->size = 0;
    return list;
}

void dl_destroy(DoubleLinkedList* list) {
    DNode* prev = list->dummy;
    while (prev != NULL) {
        DNode* curr = prev->next;
        free(prev);
        prev = curr;
    }
    free(list);
}

void dl_add(DoubleLinkedList* list, int value, int index) {
    assert(index >= 0 && index <= list->size);

    // 创建要插入的新节点
    DNode* node = (DNode*)malloc(sizeof(DNode));
    node->value = value;

    // 找到目标位置的前一个节点
    // dummy 节点天然作为头节点的前一个节点
    DNode* prev = list->dummy;
    for (int i = 0; i < index; i++) {
        prev = prev->next;
    }
    
    // 找到前一个节点后，先把下一个节点存起来备用
    DNode* next = prev->next;

    // 然后开始操作新节点的 prev 和 next，保证两个指针指向正确的位置
    node->prev = prev;
    node->next = next;

    // 新节点准备就绪后，开始处理插入逻辑
    // 让 prev 节点的 next 指向新节点，让 next 节点的 prev 节点也指向插入的这个新节点
    // 但是要注意当前可能是向链表末尾插入，所以 next 可能为空，需要做一下判断
    prev->next = node;
    if (next != NULL) {
        next->prev = node;
    }

    // 之后再维护链表 size 即可
    list->size++;
}

int dl_remove(DoubleLinkedList* list, int index) {
    assert(index >= 0 && index <= list->size); 

    // 同样从 dummy 节点开始，向后找到要删除的位置的前一个节点
    DNode* prev = list->dummy;
    for (int i = 0; i < index; i++) {
        prev = prev->next;
    }

    // 先把要删掉的节点取出来备用（注意这里 prev 永远不会为空）
    DNode* target = prev->next;

    // 提前把目标节点的值保存下来，等后面返回的时候使用
    // 否则等节点内存被释放后，就无法再访问该值了
    int value = target->value;

    // 让 prev 节点的 next 跳过 target，直接指向下一个节点
    prev->next = target->next;
    // 同时让 target 的下一个节点的 prev 也向前跳过 target
    // 但是需要注意，target 的下一个节点有可能是 NULL
    if (target->next != NULL) {
        target->next->prev = prev;
    } 
    
    // 进行到这一步时
    // prev 已经跳过了 target，指向 target 的下一个节点；下一个节点也向前跳过了 target，指向了 prev
    // 但是，target 仍然与 prev 和 next 有单方面的链接
    // 断开所有这些链接后，回收该节点的内存
    target->prev = NULL;
    target->next = NULL;
    free(target);

    // 维护一下链表的长度
    list->size --;

    // 返回目标节点的值即可
    return value;
}

int dl_get(DoubleLinkedList* list, int index) {
    assert(index >= 0 && index < list->size);  

    // 与添加或删除不同，因为 dummy 不为空，可以直接从头节点开始
    DNode* curr = list->dummy->next;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    
    // 由于我们找到的目标位置的节点，curr 最远也会指向最后一个元素， 不会为 NULL
    // 所以这里我们可以放心地直接访问 value 而不必担心越界问题
    return curr->value;
}

void dl_set(DoubleLinkedList* list, int index, int value) {
    assert(index >= 0 && index < list->size);

    // 除了常规的从头开始向后遍历外，还可以利用双链表的性质，根据目标位置选择从前向后或从后向前遍历
    // 这样在链表很长的时候，可以减少遍历的次数，从而提高效率

    DNode* curr;
    // 如果目标位置在前半部分，则从前往后找
    if (index < list->size / 2) {
        curr = list->dummy->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
    } else {
        // 如果目标位置在后半部分，则从后往前找
        curr = list->dummy->next;
        // 先移动到最后一个节点
        for (int i = 0; i < list->size - 1; i++) {
            curr = curr->next;
        }
        // 然后从后向前移动到目标位置
        for (int i = 0; i < list->size - 1 - index; i++) {
            curr = curr->prev;
        }
    }

    curr->value = value;
}


void dl_print(DoubleLinkedList* list) {
    DNode* curr = list->dummy->next;
    while (curr != NULL) {
        printf("%d->", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}