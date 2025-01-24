## 双链表

双链表是在单链表的基础上，给每个节点都增加了一个 prev 指针，用来记录当前节点的前一个节点。

但不论怎么变体，双链表的增删改查操作都和单链表类似，只是需要多维护一个 prev 指针。

下面以插入和删除为例，分别实现带 dummy 节点和不带 dummy 节点的双链表，具体的思路详见注释。

### 带 dummy 节点

#### 插入

```c
void dl_add(DoubleLinkedList* list, int value, int index) {
    assert(index >= 0 && index < list->size);

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
```

#### 删除

```c
int dl_remove(DoubleLinkedList* list, int index) {
    assert(index >= 0 && index < list->size); 

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
```

### 不带 dummy 节点

#### 插入

```c
void dl_add(DoubleLinkedList* list, int value, int index) {
    assert(index >= 0 && index <= list->size);  // 注意这里允许等于 size
    
    DNode* node = (DNode*)malloc(sizeof(DNode));
    node->value = value;
    
    // 处理空链表或头部插入的情况
    if (list->head == NULL || index == 0) {
        node->prev = NULL;
        node->next = list->head;
        if (list->head != NULL) {
            list->head->prev = node;
        }
        list->head = node;
        if (list->tail == NULL) {
            list->tail = node;
        }
    }
    // 处理尾部插入的情况
    else if (index == list->size) {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }
    // 处理中间插入的情况
    else {
        DNode* curr = list->head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        node->prev = curr->prev;
        node->next = curr;
        curr->prev->next = node;
        curr->prev = node;
    }
    
    list->size++;
}
```

#### 删除

```c
int dl_remove(DoubleLinkedList* list, int index) {
    assert(index >= 0 && index < list->size);
    assert(list->head != NULL);  // 确保链表非空
    
    DNode* target;
    int value;
    
    // 情况1：删除头节点
    if (index == 0) {
        target = list->head;
        value = target->value;
        
        list->head = target->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            // 如果删除后链表为空，需要更新 tail
            list->tail = NULL;
        }
    }
    // 情况2：删除尾节点
    else if (index == list->size - 1) {
        target = list->tail;
        value = target->value;
        
        list->tail = target->prev;
        list->tail->next = NULL;
    }
    // 情况3：删除中间节点
    else {
        target = list->head;
        for (int i = 0; i < index; i++) {
            target = target->next;
        }
        value = target->value;
        
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    
    // 清理并释放目标节点
    target->prev = NULL;
    target->next = NULL;
    free(target);
    
    list->size--;
    return value;
}
```
