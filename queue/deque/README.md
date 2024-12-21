## 双端队列

双端队列（Deque）是一种允许从两端插入和删除元素的队列。

我们可以用两种不同的底层结构来实现双端队列：循环数组或者双向链表。

### 循环数组

这里我们不使用普通的数组，而是使用循环数组，这是因为普通的数组在队首插入和队尾删除时，需要进行角标矫正，而循环数组则不需要。

普通数组为了保证队首的取值，需要在每次出队后把数组元素向前移动，这样会导致时间复杂度为 O(n)。

而循环数组则不需要，在循环数组中，我们利用 % 特性，让角标越界时自动回到数组头部或者尾部，这样就保证了队首的取值时间复杂度为 O(1)。

在具体实现时，`push_back` 和 `pop_front` 的角标矫正逻辑更符合逻辑一些，因为这两个方法的方向是正序的，始终都是从 0 开始向后递增：

- 入队操作是递增 tail 指针，最大会超过 size 的长度导致越界
- 出队操作是递增 front 指针，最大也会超过 size 的长度导致越界

这种情况下，直接对原指针正常 +1 递增后对 size 取模即可回到数组头部：

```c
deque->front = (deque->front + 1) % deque->size;
deque->back = (deque->back + 1) % deque->size;
```
 
但是 `push_front` 和 `pop_back` 则正好相反：

- 入队操作是递减 front 指针，最小会小于 0 导致越界
- 出队操作是递减 back 指针，最小会小于 0 导致越界

这种情况下，需要对角标进行矫正，矫正逻辑如下：

```c
deque->front = (deque->front - 1 + deque->size) % deque->size;
deque->back = (deque->back - 1 + deque->size) % deque->size;
```

通过对 -1 后再加上 size 再对 size 取模，能够保证角标矫正后回到数组尾部，因为额外加上的这个 size % size 等于 0，实际上不影响结果，但是却能保证左侧的操作数不为负数。

当然，判断递减后的结果是否等于 0，然后手动矫正回数组尾部也是可以的：

```c
deque->front = deque->front == 0 ? deque->size - 1 : deque->front - 1;
deque->back = deque->back == 0 ? deque->size - 1 : deque->back - 1;
```

整体上来说，双端队列的实现与普通的循环数组没什么不同，核心还是依赖 % 运算符搭配循环数组，让角标永远处于 `[0, size - 1]` 这个区间内，从而保证所有操作的复杂度都是 O(1)。

### 双向链表

其实双向链表本身就是个双端队列，只是封装了几个方法而已。

维护了尾指针的双向链表本身就支持在队首和队尾以 O(1) 的时间复杂度进行插入和删除操作，所以实现起来非常简单。

这里就不再赘述了。


### 优化方向

这里补充一个优化点：在扩容时，主动将队列放在队列的中间位置，保证前后都有空间进行插入。

假设队列的排列为：`[1, 2, 3, 4, 5, null]`, 这种情况下调用 `addFirst` 进行入队操作，由于队列已满会优先进行扩容。扩容后队列的情况为：`1, 2, 3, 4, 5, null, null, null, null, null, null`。

然后继续调用 `addFirst(-1)` 进行插入，经过 `(front - 1 + len) % len` 的矫正操作以后，`front` 会定位到数组最后一位：

`1, 2, 3, 4, 5, null, null, null, null, null, -1`

此时，一个刚刚扩容完成的队列转化为了循环队列，这种情况下，由于数组元素的位置不连续，对命中 CPU 缓存不友好，可以考虑如下优化方案：

在扩容时，主动将队列放在队列的中间位置，保证前后都有空间进行插入。

```java
private void resize(int newCapacity) {
    E[] newData = (E[])new Object[newCapacity];
    
    // 计算新数组中的起始位置
    int start = (newCapacity - size) / 2;
    int j = start;
    
    // 从 front 开始，复制 size 个元素
    for (int i = 0; i < size; i++) {
        // 通过取模来处理循环的情况
        newData[j++] = data[(front + i) % data.length];
    }
    
    // 更新索引
    front = start;
    tail = j;
    
    data = newData;
}
```

这样扩容完以后的数组：`[null, null, -1, 1, 2, 3, 4, 5, null, null]`，从而保证队列前后都有空间可以插入新元素。