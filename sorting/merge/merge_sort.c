#include "merge_sort.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void merge(int* arr, int* temp, int l, int m, int r) {
  int i = l, j = m + 1, k = 0;
  while(i <= m && j <= r) {
    if (arr[i] < arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while(i <= m) temp[k++] = arr[i++];
  while(j <= r) temp[k++] = arr[j++];
  
  for (int i = 0; i < r - l + 1; i++) {
    arr[l + i] = temp[i];
  }
}

static void mergeSort(int* arr, int* temp, int l, int r) {
  if (l >= r) return; 
  int m = l + (r - l) / 2; // avoid  integer overflow
  mergeSort(arr, temp, l, m);
  mergeSort(arr, temp, m + 1, r);
  if (arr[m] > arr[m + 1]) 
    merge(arr, temp, l, m, r);
}

void recursiveMergeSort(int* arr, int length) {
  int temp[length];
  mergeSort(arr, temp, 0, length - 1);
}

void iterativeMergeSort(int* arr, int length) {
  int temp[length];
  for (int size = 1; size <= length - 1; size = size * 2) {
    for (int left = 0; left + size <= length - 1; left += size * 2) {
      int mid = left + size - 1;
      int right = MIN(left + size * 2 - 1, length - 1);
      if (arr[mid] > arr[mid + 1])
        merge(arr, temp, left, mid, right);
    }
  }
}


