#include <stdio.h>
#include "sorting.h"
#include "helper.h"

void selectionSort(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    int minIndex = i;
    for (int j = i; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    swap(&arr[i], &arr[minIndex]);
  }
}

void insertionSort(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    int target = arr[i];
    int j = i;
    while (j - 1 >= 0 && arr[j - 1] > target) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = target;
  }
}

