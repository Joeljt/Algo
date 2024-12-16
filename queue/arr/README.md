## 数组队列

数组队列的实现非常简单，数组本身就是一个队列，数组头部是队列头，数组尾部是队列尾。

因此，在这个实现中，我们本质上只是对数组的 `addLast` 和 `removeFirst` 方法进行了封装。

### 实现

```c
void aq_enqueue(ArrayQueue* queue, int value) {
  addLast(queue->array, value);
}
```

```c
int aq_dequeue(ArrayQueue* queue) {
  return removeFirst(queue->array);
}
```

### 复杂度分析

入队操作只是对数组尾部进行操作，因此时间复杂度为 O(1)。

出队操作需要对从数组头部移除元素，之后需要将所有元素向前移动一个位置，保证数组头部是队列头，因此时间复杂度为 O(n)。

出于这个原因，几乎不会使用数组来实现一个普通队列，因为性能太差；更常用 [循环队列](../circular/README.md) 或 [链表队列](../linked/README.md)。

