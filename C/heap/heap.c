#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int* data;
    int size;
    int capacity;
};

static void resizeHeap(Heap* heap, int newCapacity) {
  int* newData = (int*)malloc(sizeof(int) * newCapacity);

  for(int i = 0; i < heap->size; i++) {
    newData[i] = heap->data[i];
  }

  free(heap->data);

  heap->data = newData;
  heap->capacity = newCapacity;
}

static void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

static void swim(Heap* heap, int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (heap->data[index] < heap->data[parent]) {
      swap(&heap->data[index], &heap->data[parent]);
      index = parent;
    } else {
      break;
    }
  }
}

static void sink(Heap* heap) {
  int index = 0;
  while (1) {
    // 从堆顶开始向下，找到子节点
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    // 依次用左右节点和当前值做对比，看哪个更大，并记录下标位置
    if (left < heap->size && heap->data[left] < heap->data[largest])
      largest = left;

    if (right < heap->size && heap->data[right] < heap->data[largest])
      largest = right;

    // 如果和左右节点比对完成以后，发现 index 并没有变化
    // 则说明当前位置已经是最大值，跳出循环即可
    if (index == largest) break;

    // 否则，就把当前 index 和目标位置进行交换
    swap(&heap->data[index], &heap->data[largest]);

    // 然后更新 index 后继续
    index = largest;
  }
}

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
}

void push(Heap* heap, int value) {
  if (heap->size == heap->capacity)
    resizeHeap(heap, heap->capacity * 2);

  heap->data[heap->size] = value; 

  swim(heap, heap->size);
  heap->size++;
}

int pop(Heap* heap) {
  int result = heap->data[0];

  heap->data[0] = heap->data[heap->size - 1];
  heap->size--;

  if (heap->size > 0)
    sink(heap);

  if (heap->size > 0 && heap->size == heap->capacity / 4)
    resizeHeap(heap, heap->capacity / 2);

  return result;
}

int peek(Heap* heap) {
  return heap->data[0];
}

void printHeap(Heap* heap) {
  for (int i = 0; i < heap->size; i++) {
    printf("%d ", heap->data[i]);
  }
  printf("\n");
}

