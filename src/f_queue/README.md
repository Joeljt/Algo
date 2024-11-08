## 队列

队列是一种线性数据结构，类似生活中的排队，先进先出。

核心操作以及时间复杂度：
- `enqueue(E e)`：入队，O(1)
- `dequeue()`：出队，数组队列 O(n)，循环队列 O(1)
- `getFront()`：获取队首元素，O(1)
- `isEmpty()`：判断队列是否为空，O(1)
- `getSize()`：获取队列中元素个数，O(1)

### 数组队列

基于数组实现的队列比较好理解，从数组末尾入队（addLast），从数组开头出队（removeFirst）。

但是数组的 `removeFirst` 操作需要把数组中所有元素向前移动一位，所以时间复杂度为 O(n)，需要使用循环队列来优化。

### 循环队列

由于数组队列的 `dequeue` 操作时间复杂度为 O(n)，所以需要使用循环队列来优化。

核心思路是：
- 单独维护队首队尾下标，`front` 指向队首元素，`tail` 指向队尾元素的下一个元素
- `front` 和 `tail` 的自增操作都需要增加 `%` 取余操作，从而实现循环

#### 实现方案

1. 主动浪费一个空间，完全依赖 `front` 和 `tail` 的相对位置关系来判断队列状态：

    - 当 `front` 和 `tail` 相等时，表示队列为空
    - `tail` 向前再进一步如果与 `front` 相等，表示队列为满 （`(tail+1) % length == front`）
    - `tail` > `front` 时，说明队列顺序正常，队列元素个数为：`tail` - `front`
    - `tail` < `front` 时，说明队列处于循环状态，队列元素个数为：`len` - `front` + `tail`

2. 不浪费空间，但是需要自己维护队列元素个数（逻辑更简单）

    - `size` 为 0 时队列为空，`size` == `len` 时队列为满

#### 遍历

1. 每个元素都有 `front` 个位置的偏移：

```java
for (int i = 0; i < size; i++) {
    E e = data[(i + front) % length];
}
```

2. 从 `front` 开始向后依次遍历：


```java
for (int i = front; i != tail; i = (i + 1) % length) {
    E e = data[i];
}
```

### 双端队列

TODO