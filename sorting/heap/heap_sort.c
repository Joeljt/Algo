#include "heap_sort.h"
#include "helper.h"

static void sift_down(int* arr, int length) {

}

static void heapify(int* arr, int length) {

}

void heapSort(int* arr, int length) {
  heapify(arr, length);
  for (int i = 0; i < length; i++) {
    swap(&arr[0], arr[length - 1 - i]); // 将最值放到末尾
    sift_down(arr, length - i - 1); // 重新构建最大堆，满足堆条件
  }
}


