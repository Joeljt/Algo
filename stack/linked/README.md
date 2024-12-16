## 链表栈

基于链表实现的栈，利用链表头部增加和删除的复杂度为 O(1) 的特性，实现栈的 push 和 pop 操作。

也就是说，链表头部是栈顶，链表尾部是栈底。

### 时间复杂度

- push: O(1)
- pop: O(1)
- peek: O(1)

### 空间复杂度

- O(n)

### 实现

#### 入栈

```c
void ls_push(LinkedStack* stack, int value) {
  ll_addFirst(stack->list, value);
}
```

#### 出栈

```c
int ls_pop(LinkedStack* stack) {
  return ll_removeFirst(stack->list);
}
```

#### 查看栈顶元素
    
```c
int ls_peek(LinkedStack* stack) {
  return ll_getFirst(stack->list, 0);
}
```
