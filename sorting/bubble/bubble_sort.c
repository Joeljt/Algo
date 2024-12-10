#include <stdio.h>
#include "../helper.h"
#include "bubble_sort.h"

void bubbleSort(int* arr, int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = 0; j < length - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

void bubbleSort2(int* arr, int length) {
  for (int i = 0; i < length - 1; i++) {
    bool isSwapped = false;
    for (int j = 0; j < length - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        isSwapped = true;
      }
    }
    if (!isSwapped) break;
  }
}

void bubbleSort3(int* arr, int length) {
  for (int i = 0; i < length - 1;) {
    int lastSwappedIndex = 0;
    for (int j = 0; j < length - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        lastSwappedIndex = j + 1;
      }
    }
    i = length - lastSwappedIndex;
  }
}

