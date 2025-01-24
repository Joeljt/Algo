## 数组栈

基于数组实现的栈，利用数组尾部增加和删除的复杂度为 O(1) 的特性，实现栈的 push 和 pop 操作。

也就是说，数组尾部是栈顶，数组头部是栈底。

### 时间复杂度

- push: O(1)
- pop: O(1)
- peek: O(1)

### 空间复杂度

- O(n)

### 实现

#### 入栈

```c
void as_push(ArrayStack* stack, int value) {
  addLast(stack->array, value);
}
```

#### 出栈

```c
int as_pop(ArrayStack* stack) {
  return removeLast(stack->array);
}
```

#### 查看栈顶元素

```c
int as_peek(ArrayStack* stack) {
  return getElement(stack->array, getSize(stack->array) - 1);
}
```
