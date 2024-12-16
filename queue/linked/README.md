## 链表队列

除了数组以外，我们还可以考虑使用链表来实现一个队列。

对于链表来说，链表头是一个插入或者删除都可以达到 O(1) 效率的节点，因此链表头出队或者入队都可以。

但是在默认的单链表实现中，链表尾插入和删除都是 O(n) 效率的，但我们可以通过增加一个尾指针来实现对链表尾 O(1) 效率的插入操作。

综上所述，我们可以用一个带有尾指针的链表来实现一个队列，链表头做队首，链表尾做队尾。

链表队列的入队出队复杂度都是 O(1)，性能要远远好过数组队列。

### 实现

由于我们这里用来实现队列的链表是带有尾指针的，所以我们在入队或出队的时候，都需要对尾指针进行维护。

#### 入队

在队列为空时，头指针和尾指针都为空，所以我们直接创建一个新节点，并让头尾指针都指向这个新节点。

当队列不为空时，我们直接将新节点插入到尾指针指向的节点后面，并让尾指针指向这个新节点。

```c
void lq_enqueue(LinkedQueue* queue, int value) {
    if (queue != NULL) {
        if (queue->tail == NULL) {
            queue->tail = lq_createLNode(value, NULL);
            queue->head = queue->tail;
        } else {
            queue->tail->next = lq_createLNode(value, NULL);
            queue->tail = queue->tail->next;
        }
        queue->size++;
    }
}
```

这样我们就实现了尾指针始终指向链表尾元素的效果，每次入队新元素，尾指针都会移动到该元素上。

#### 出队

出队时，我们把当前头节点缓存下来等后面返回的时候使用，之后直接跳过当前的头节点，指向下一个节点即可。

但是要注意的一点是，如果出队以后，队列变空了，那么我们需要将尾指针也置空。

同时不要忘记回收出队节点的内存，否则会造成内存泄漏。

```c
void lq_dequeue(LinkedQueue* queue) {
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
```

#### 查看队首元素

peek 操作直接查看队首元素即可，不需要遍历也不涉及移动。peek操作总是O(1)的。

```c
int lq_peek(LinkedQueue* queue) {
    if (lq_isEmpty(queue)) {
        return -1;
    }
    return queue->head->data;
}
```