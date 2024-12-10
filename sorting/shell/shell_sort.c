#include "shell_sort.h"

void shellSort(int* arr, int length) {
  int gap = length / 2;
  while (gap >= 1) {
    for (int i = gap; i < length; i++) {
      int target = arr[i];
      int j = i;
      while (j - gap >= 0 && arr[j - gap] > target) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      arr[j] = target;
    }
    gap /= 2;
  }
}

void shellSort2(int* arr, int length) {
  int gap = 1;
  while (gap < length)
    gap = 3 * gap + 1;

  while (gap >= 1) {
    for (int i = gap; i < length; i++) {
      int target = arr[i];
      int j = i;
      while (j - gap >= 0 && arr[j - gap] > target) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      arr[j] = target;
    }
    gap /= 3;
  }
}