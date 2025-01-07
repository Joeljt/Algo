#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 需要在文件开头添加 swap 函数的实现
static void swap(void** arr, int i, int j) {
    void* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 在 0 开始的数组中，找到索引为 index 的节点的父节点、左子节点、右子节点
int parent(int index) { return (index - 1) / 2; }
int left(int index) { return 2 * index + 1; }
int right(int index) { return 2 * index + 2; }

struct Heap {
  void** data;
  int size;
  int capacity;
  int (*compare)(void*, void*);
};

Heap* heap_create(int capacity, int (*compare)(void*, void*)) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->data = (void**)malloc(sizeof(void*) * capacity);
  heap->size = 0;
  heap->capacity = capacity;
  heap->compare = compare;
  return heap;
}

void heap_destroy(Heap* heap) {
  free(heap->data);
  free(heap);
}

void heap_resize(Heap* heap, int new_capacity) {
  heap->data = (void**)realloc(heap->data, sizeof(void*) * new_capacity);
  heap->capacity = new_capacity;
}

// 对索引为 index 的节点进行上浮操作
// 过程中检查当前元素是否大于其父节点，是的话就交换，然后重复这个过程，直到该节点到达其应该在的位置
void sift_up(Heap* heap, int index) {
  int parent_index = parent(index);
  while (index > 0 && heap->compare(heap->data[index], heap->data[parent_index]) > 0) {
    swap(heap->data, index, parent_index);
    index = parent_index;
    parent_index = parent(index);
  }
}

// 上浮操作的递归实现
// 完成交换后用新的 index 位置重复整个过程，直到不满足条件后结束
void sift_up_recursive(Heap* heap, int index) {
  int parent_index = parent(index);
  if (parent_index >= 0 && heap->compare(heap->data[index], heap->data[parent_index]) > 0) {
    swap(heap->data, index, parent_index);
    sift_up_recursive(heap, parent_index);
  }
}

// 对索引为 index 的节点进行下沉操作
void sift_down(Heap* heap, int index) {
  int size = heap->size;
  while (true) {
    int largest = index;
    int l = left(index);
    int r = right(index);
        
    if (l < size && heap->compare(heap->data[l], heap->data[largest]) > 0)
      largest = l;
    if (r < size && heap->compare(heap->data[r], heap->data[largest]) > 0)
      largest = r;
            
    if (largest == index)
      break;
            
    swap(heap->data, index, largest);
    index = largest;
  }
}

// 对索引为 index 的节点进行下沉操作
// 下沉的时候需要依次与当前节点的左右子节点进行比较，取更大的那个进行交换
// 然后重复这个过程，直到找到该节点应该在的位置
void sift_down_recursive(Heap* heap, int index) {
  int l = left(index);
  int r = right(index);
  int largest = index;
  // 在节点不越界的情况下，比较大小
  if (l < heap->size && heap->compare(heap->data[l], heap->data[largest]) > 0) {
    largest = l;
  }
  // 同样，右节点不越界的情况下，比较大小
  if (r < heap->size && heap->compare(heap->data[r], heap->data[largest]) > 0) {
    largest = r;
  }
  // 判断当前节点是不是整个子树中的最大值
  if (index != largest) {
    // 如果不是的话，把当前节点和较大的节点做交换
    swap(heap->data, index, largest);
    // 然后对新节点递归继续下沉
    sift_down_recursive(heap, largest);
  }
}

void heap_push(Heap* heap, void* value) {
  if (heap->size == heap->capacity) {
    heap_resize(heap, heap->capacity * 2);
  }
  // 在数组最后一个位置插入新元素
  heap->data[heap->size] = value;
  heap->size++;
  // 对新元素上浮，构建最大堆
  sift_up(heap, heap->size - 1);
  // sift_up_recursive(heap, heap->size - 1);
}

void* heap_pop(Heap* heap) {
  if (heap->size == 0) return NULL;
  // 取出堆顶元素
  void* result = heap->data[0];
  // 将最后一个元素放到堆顶，下沉
  heap->data[0] = heap->data[heap->size - 1];
  // 删除最后一个元素
  heap->data[heap->size - 1] = NULL;
  // 维护堆的大小
  heap->size--;
  // 对新堆顶元素下沉，构建最大堆
  sift_down(heap, 0);
  // sift_down_recursive(heap, 0);
  
  // 如果堆的大小小于容量的四分之一，并且堆的大小大于 2，则缩小堆的容量
  if (heap->size < heap->capacity / 4 && heap->capacity / 2 != 0) {
    heap_resize(heap, heap->capacity / 2);
  }

  return result;
}

void* heap_peek(Heap* heap) {
  if (heap->size == 0) return NULL;
  return heap->data[0];
}

void heap_print(Heap* heap) {
  printf("Heap: ");
  for (int i = 0; i < heap->size; i++) {
    printf("%d ", *(int*)heap->data[i]);
  }
  printf("\n");
}

