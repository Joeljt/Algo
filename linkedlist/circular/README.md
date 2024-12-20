## 循环链表

循环链表是在普通链表的基础上增加了循环特性，即让最后一个节点指向第一个节点。

和普通链表一样，使用虚拟头节点会极大程度地简化操作，但是出于练习的目的，这里循环链表的实现没有使用 dummy 节点。

这里我们的实现基于一个维护了尾指针的单链表，因为相较于维护头指针，维护尾指针的实现更简单。

tail 永远指向最后一个节点，tail->next 即是第一个节点，这样可以很方便地以 O(1) 的时间复杂度对链表首尾进行操作。

相比较之下，如果维护的是 head 指针，想操作链表尾部，就需要遍历整个链表才可以做到。

### 实现

这里我们使用一个结构体来表示循环链表，结构体中包含一个尾指针，和一个表示链表大小的 size 变量。

```c 
typedef struct CircularLinkedList {
    CNode *tail;
    int size;
} CircularLinkedList;
```

在这个基础上，我们实现为这个循环链表增加在任意位置插入节点的方法，忽略边界情况的处理。

```c
void cl_add(CircularLinkedList *list, int value, int index) {
    CNode *node = create_node(value);

    // 需要先考虑链表为空的情况，如果链表为空，新节点就是尾节点，同时也是头节点
    // 自己指向自己形成空环
    if (list->tail == NULL || list->size == 0) {
        list->tail = node;
        node->next = node;
        return;
    }

    // 如果要插入的位置是链表头部，则直接维护指针关系即可
    // list->tail->next 就是链表的第一个节点，让新节点指向它即可
    // 由于我们维护的是尾指针，所以在头部插入不影响尾指针的指向
    if (index == 0) {
        node->next = list->tail->next;
        list->tail->next = node;
        return;
    }

    // 如果要插入的位置是链表尾部，就需要维护尾指针
    // 先让新节点指向原来尾节点指向的节点，也就是头节点
    // 再让原来的尾节点指向新节点，完成插入逻辑
    // 最后让新节点成为新的尾节点，维护尾指针
    if (index == list->size) {
        node->next = list->tail->next;
        list->tail->next = node;
        list->tail = node;
        return;
    }

    // 如果要插入的位置在链表中间，就从链表头开始遍历，找到目标位置的前一个节点，
    // 然后维护指针关系即可
    CNode *prev = list->tail->next;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    node->next = prev->next;
    prev->next = node;

    list->size++;
}
```

删除节点逻辑很简单，找到目前位置的前一个节点，然后维护指针关系即可。**真正麻烦的是维护尾指针**。

```c
int cl_remove(CircularLinkedList *list, int index) {
    if (list->size == 0) return -1;

    // 从头节点开始，找到目标位置的前一个节点
    CNode *prev = list->tail->next;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    
    // 先取出目标节点
    CNode *target = prev->next;
    int value = target->value;

    // 需要判断删除的是不是链表里唯一的节点
    // 如果是，则需要维护尾指针为 NULL
    if (target == target->next || list->size == 1) {
        list->tail = NULL;
    } else {
        // 删除节点只需要跳过目标节点即可
        prev->next = target->next;
        // 然后检查删除的是否是尾节点，如果是，还需要维护尾指针
        if (target == list->tail) {
            list->tail = prev;
        }
    }

    free(target);
    list->size--;

    return value;
}
```

可以发现，由于没有 dummy 节点，实现逻辑上要复杂很多，下面我们来看看使用 dummy 节点的实现。

```c
void cl_add(CircularLinkedList *list, int value, int index) {
    assert(list != NULL);
    assert(index >= 0 && index <= list->size);

    CNode *node = create_node(value);

    // 找到插入位置的前一个节点
    // 从 dummy 开始遍历，需要特殊处理头部插入的情况
    CNode *prev = list->dummy;
    for (int i = 0; i < index; i++) {
        prev = prev->next;
    }
    
    // 插入操作统一处理，不需要考虑是否为空链表
    node->next = prev->next;
    prev->next = node;
    
    list->size++;
}

int cl_remove(CircularLinkedList *list, int index) {
    assert(list != NULL);
    assert(index >= 0 && index < list->size);

    // 找到删除位置的前一个节点
    CNode *prev = list->dummy;
    for (int i = 0; i < index; i++) {
        prev = prev->next;
    }

    // 取出要删除的节点
    CNode *target = prev->next;
    int value = target->value;

    // 删除节点
    prev->next = target->next;
    free(target);
    
    list->size--;
    return value;
}
```

很明显，代码逻辑更简洁也更容易维护，各种特殊处理和边界判断都可以忽略掉。

代码的简洁性和可维护性比空间效率更重要，何况只是浪费了一个节点的空间，可以带来如此巨大的好处，还是更推荐使用 dummy 节点处理链表。如果有尾部操作的必要，可以考虑额外维护一个尾指针。