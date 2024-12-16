## 循环队列

循环队列本质上是对数组队列的优化和改进。

在我们之前实现的数组队列中，出队操作需要将队首元素后面的所有元素向前移动，这个操作的复杂度是 O(n) 的，效率很低。

但是假设在队首元素出队之后，我们不用将所有元素往前移动，而是将队列的队首指针向后移动，去找当前数组中的第一个元素，那我们就将出队操作的复杂度优化到了 O(1)。

但是这样又会带来一个问题，那就是数组中可能存在很多空闲的元素，这些元素我们明明可以利用，但是因为队首指针已经移动到了数组末尾，所以无法被利用。

为了解决这个问题，我们可以将数组想象成一个环，当队首指针移动到数组末尾时，再从数组头部开始，这样就形成了一个环形结构，这就是循环队列。

### 实现

队列本身的操作是很简单的，循环队列的关键点在于首尾指针的移动和临界点的判断。

核心思路是：

- 单独维护队首指针和队尾指针，`front` 指向队首元素，`rear` 指向队尾元素的下一个位置。
- `front` 和 `rear` 的自增操作都需要对 `size` 取模，以实现循环的效果。

实现方案有两种：

1. 主动浪费一个空间，完全依赖 `front` 和 `rear` 的相对位置来判断队列是否为空或满。  
    - `front` 与 `rear` 相等时，队列为空。
    - `rear` 的下一个位置与 `front` 相等时，队列满，即 `(rear + 1) % size == front`。
    - `rear` > `front` 时，队列顺序正常，还未开启循环，队列元素个数为 `rear - front`。
    - `rear` < `front` 时，队列处于循环状态，队列元素个数为 `size - front + rear`。

2. 不浪费空间，但是需要自己维护队列元素个数，逻辑上更简单。
    - `count` 表示队列元素个数, `count` 的值在 `[0, size]` 之间。

需要注意的一点是，循环队列的实现不能完全复用之前的动态数组，而要重新实现，因为 resize 的逻辑有变化。

```c
// 循环队列的扩容不能用 realloc 来实现，因为我们需要对元素位置做调整
static void resize(CircularQueue *queue, int newCapacity) {
    int *newArray = (int *)malloc((newCapacity + 1) * sizeof(int));
    if (newArray == NULL) {
        return;
    }
    for (int i = 0; i < queue->count; i++) {
        newArray[i] = queue->array[(queue->front + i) % queue->size];
    }
    free(queue->array);
    queue->array = newArray;
    queue->size = newCapacity + 1;
    queue->front = 0;
    queue->rear = queue->count;
}
```
