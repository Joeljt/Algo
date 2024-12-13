# 链表

链表是一种物理存储单元上非连续、非顺序的存储结构，数据元素的逻辑顺序是通过链表中的指针链接次序实现的。

链表不需要浪费额外的内存空间，但是它的访问效率比数组要低很多，因为只能通过头节点依次向后遍历才能找到特定的节点，而不能像数组一样直接通过下标访问特定的元素。

## 单向链表

### 基本结构

```c
typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;
```

### 基本操作

```c
void add(LinkedList* list, int index, int data) {
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;
  prev->next = createNode(data, prev->next);
  list->size ++;
}

void remove(LinkedList* list, int index) {
  Node* prev = list->dummy;
  for(int i = 0; i < index; i++)
    prev = prev->next;
  Node* cur = prev->next;
  prev->next = cur->next;
  free(cur);
  list->size --;
}
```

## 双向链表

```c
typedef struct DNode {
    int val;
    struct DNode* prev;
    struct DNode* next;
} DNode;

typedef struct {
    DNode* head;
    DNode* tail;
    int size;
} DoublyLinkedList;
```

## 循环链表

