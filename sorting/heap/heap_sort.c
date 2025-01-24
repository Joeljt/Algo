#include "heap_sort.h"
#include "../helper.h"
#include "datastruct/heap/basic/heap.h"
#include <stdlib.h>

static void sift_down(int* arr, int length, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int max = i; // 假设当前节点就是最大值

  // 找到左右节点中的最大值
  if (left < length && arr[left] > arr[max]) {
    max = left;
  }
  if (right < length && arr[right] > arr[max]) {
    max = right;
  }

  // 如果最大值不是当前节点，则交换
  if (max != i) {
    swap(&arr[i], &arr[max]);
    // 递归向下调整
    sift_down(arr, length, max);
  }
}

static void sink(int* arr, int n, int i) {
    int temp = arr[i];  // 保存当前节点值
    
    // 沿着较大的子节点向下筛选
    for (int j = 2 * i + 1; j < n; j = 2 * j + 1) {
        // 找到较大的子节点
        if (j + 1 < n && arr[j] < arr[j + 1]) {
            j++;
        }
        
        // 如果当前值已经大于子节点，结束筛选
        if (temp >= arr[j]) {
            break;
        }
        
        // 子节点上移
        arr[i] = arr[j];
        i = j;
    }
    
    arr[i] = temp;  // 放入最终位置
}

int compare(void* a, void* b) {
  return *(int*)a - *(int*)b;
}

void heapSort(int* arr, int length) {
  Heap* heap = heap_create(length, compare);
  for (int i = 0; i < length; i++) {
    int* num = malloc(sizeof(int));
    *num = arr[i];
    heap_push(heap, num);
  }
  for (int i = length - 1; i >= 0; i--) {
    arr[i] = *(int*)heap_pop(heap);
  }
  heap_destroy(heap);
}

void heapSort1(int* arr, int length) {
  // 建堆
  for (int i = length / 2 - 1; i >= 0; i--) {
    sift_down(arr, length, i);
  }

  // 倒序遍历，因为需要将最大值放到末尾
  for (int i = length - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]); // 将最值放到末尾
    sift_down(arr, i, 0); // 重新构建最大堆，满足堆条件
  }
}

void heapSort2(int* arr, int length) {
  for (int i = length / 2 - 1; i >= 0; i--) {
    sink(arr, length, i);
  }

  for (int i = length - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    sink(arr, i, 0);
  }
} 

