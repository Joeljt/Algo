## 单向链表

单向链表是最基本的链表结构，所有的复杂链表结构都是基于单向链表的变体。

链表的核心结构是 Node 节点，包含数据和指向下一节点的指针。只要给定一个链表头节点，就应该可以使用递归或者迭代的方式实现基本操作。

在实际中，因为操作节点过于繁琐，一般会封装一个 LinkedList 结构体，只对外暴露操作接口。

同时，实践中一般会使用虚拟头结点，保证链表头结点不会为空，以简化操作。

### 基本结构

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* dummy; // 虚拟头结点，用来简化操作
    int size;
} LinkedList;
```

### 基本操作

#### 创建链表

利用虚拟头节点，创建链表的时候，直接初始化一个节点作为 HEAD 节点的前一个节点。

这样可以保证链表一定不为空，后面的操作就不需要单独处理头结点为空的情况。

```c
LinkedList* ll_create() {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  list->dummy = (Node*)malloc(sizeof(Node));
  list->dummy->next = NULL;
  list->size = 0;
  return list;
}
```

#### 添加元素

添加元素的时候，从 0 开始向后查找，找到目标位置的前一个位置，然后进行插入。

```c
void ll_add(LinkedList* list, int index, int data) {
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;

  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  // 让新节点指向前一个节点指向的位置
  // [1 -> (2|4) -> 3]
  node->next = prev->next;
  // 更新前一个节点的指向，指向新节点，完成插入
  // [1 -> 2 -> 4 -> 3]
  prev->next = node;

  list->size ++;
}
```

#### 删除元素

删除元素与添加元素的思路类似，找到目标位置的前一个位置，然后断开链接，之后释放目标位置的节点。

```c
int ll_remove(LinkedList* list, int index) {  
  // 找到要删除的节点的前一个节点位置
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;

  // 通过 prev->next 找到要删除的节点
  Node* cur = prev->next;
  // 直接跳过当前节点，并指向下一个节点，从而断开链接
  prev->next = cur->next;
  int data = cur->data;

  // !!! 释放目标节点，回收内存，否则就会导致内存泄漏
  // 注意这里释放的是 cur 节点，而不是 prev 节点
  free(cur);

  list->size --;
  return data;
}
```

#### 修改元素

修改元素的时候，找到目标位置，然后直接修改数据。

```c
void ll_set(LinkedList* list, int index, int data) {
  Node* current = list->dummy->next;
  for(int i = 0; i < index; i++)
    current = current->next;
  current->data = data;
}
```

#### 获取元素

获取元素的时候，从 0 开始向后查找，找到目标位置，然后返回数据。

```c
int ll_get(LinkedList* list, int index) {
  // 注意这里直接从真实头节点开始，而不是虚拟头节点，因为虚拟头节点是没有数据的
  Node* current = list->dummy->next;
  for(int i = 0; i < index; i++)
    current = current->next;
  return current->data;
}
```

### 练习