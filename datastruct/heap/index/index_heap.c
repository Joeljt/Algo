#include "index_heap.h"

struct IndexHeap {
  int* data;      // 原始数据数组
  // indexes 是从堆的角度描述的原始数组，即从堆顶开始依次向下，堆里每个位置的元素在原始数组中的下标
  // indexes[0] = 3：堆顶位置存放的是原始数组中下标为3的元素(42)
  // indexes[1] = 1：堆的第二个位置存放的是原始数组中下标为1的元素(28)
  int* indexes;   
  // reverse 是从原始数据的角度描述的堆，即当前这个位置的元素在堆里是什么位置
  // reverse[3] = 0：原始数组中下标为3的元素(42)在堆中位于位置0（堆顶）
  // reverse[1] = 1：原始数组中下标为1的元素(28)在堆中位于位置1
  int* reverse;   
  int size;       // 堆大小
  int capacity;   // 堆容量
};

static void ih_swap_indexes(IndexHeap* ih, int a, int b) {
  int temp = ih->indexes[a];
  ih->indexes[a] = ih->indexes[b];
  ih->indexes[b] = temp;

  // 更新反向索引数组
  // 反向索引数组存储的是：堆中的每个位置，对应的原始数组中的下标
  // 比如，reverse[3] = 0：堆中下标为3的元素(42)在原始数组中下标为0
  // 比如，reverse[1] = 1：堆中下标为1的元素(28)在原始数组中下标为1
  ih->reverse[ih->indexes[a]] = a;
  ih->reverse[ih->indexes[b]] = b;
}

static void ih_resize(IndexHeap* ih, int new_capacity) {
  // 重新分配内存
  ih->data = (int*)realloc(ih->data, sizeof(int) * new_capacity);
  ih->indexes = (int*)realloc(ih->indexes, sizeof(int) * new_capacity);
  ih->reverse = (int*)realloc(ih->reverse, sizeof(int) * new_capacity);
  // 更新容量
  ih->capacity = new_capacity;
}

// 我们判断的仍然是原始数据，但是操作的是索引数组，这个很好理解
// 但是我们访问原始数据的时候，也需要通过索引数组里的索引去访问，而不是直接访问原始数据
// 因为原始数据的顺序是不变的，但是根据索引数组里的索引去访问，才能得到正确的堆结构数据
static void ih_shift_up(IndexHeap* ih, int i) {
  while (i > 0 && ih->data[ih->indexes[i]] > ih->data[ih->indexes[(i - 1) / 2]]) {
    ih_swap_indexes(ih, i, (i - 1) / 2);
    i = (i - 1) / 2;
  }
}

static void ih_shift_down(IndexHeap* ih, int i) {
  while (2 * i + 1 < ih->size) {
    int j = 2 * i + 1;
    if (j + 1 < ih->size && ih->data[ih->indexes[j + 1]] > ih->data[ih->indexes[j]]) {
      j++;
    }
    if (ih->data[ih->indexes[i]] >= ih->data[ih->indexes[j]]) {
      break;
    }
    ih_swap_indexes(ih, i, j);
    i = j;
  }
}

IndexHeap* ih_create(int capacity) {
  IndexHeap* ih = (IndexHeap*)malloc(sizeof(IndexHeap));

  // 分配内存
  ih->data = (int*)malloc(sizeof(int) * capacity);
  ih->indexes = (int*)malloc(sizeof(int) * capacity);
  ih->reverse = (int*)malloc(sizeof(int) * capacity);

  // 初始化大小和容量
  ih->size = 0;
  ih->capacity = capacity;

  // 初始化反向索引数组, -1 表示该位置的元素不在堆中
  for (int i = 0; i < capacity; i++) {
    ih->reverse[i] = -1;
  }

  return ih;
}

void ih_destroy(IndexHeap* ih) {
  free(ih->data);
  free(ih->indexes);
  free(ih->reverse);
  free(ih);
}

void ih_push(IndexHeap* ih, int value) {
  if (ih->size == ih->capacity) {
    ih_resize(ih, ih->capacity * 2);
  }
  // 原始数据正常插入数组
  ih->data[ih->size] = value;
  // 索引数组中插入索引
  ih->indexes[ih->size] = ih->size;
  // 反向索引数组中插入索引
  ih->reverse[ih->size] = ih->size;
  // 元素数量增加
  ih->size++;
  // 对索引数组进行上浮操作
  ih_shift_up(ih, ih->size - 1);
}

int ih_pop(IndexHeap* ih) {
  // 获取堆顶元素
  int ret = ih->data[ih->indexes[0]];
  // 交换堆顶元素和最后一个元素
  ih_swap_indexes(ih, 0, ih->size - 1);
  // 元素数量减少
  ih->size--;
  // 对索引数组进行下沉操作
  ih_shift_down(ih, 0);
  return ret;
}

void ih_update(IndexHeap* ih, int i, int value) {
  // 更新原始数据
  ih->data[i] = value;
  // 对索引数组进行上浮或下沉操作
  // 因为无法确定更新后的数据的变化方向，所以两个方法都需要调用，但是只有一个会生效
  ih_shift_up(ih, ih->reverse[i]);
  ih_shift_down(ih, ih->reverse[i]);
}

void ih_print(IndexHeap* ih) {
  printf("IndexHeap: ");
  for (int i = 0; i < ih->size; i++) {
    printf("%d ", ih->data[ih->indexes[i]]);
  }
  printf("\n");
}