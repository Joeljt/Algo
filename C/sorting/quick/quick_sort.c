#include "quick_sort.h"
#include "../helper.h"

int partition(int* arr, int left, int right) {
    int pivot = arr[left];
    int l = left + 1, r = right;
    while(l <= r) {
        while(l <= r && arr[l] <= pivot) l++;
        while(l <= r && arr[r] > pivot) r--;
        if (l < r) {
            swap(&arr[l], &arr[r]);
        }
    }
    swap(&arr[left], &arr[r]);
    return r;
}

static void sort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = partition(arr, left, right);
    sort(arr, left, pivot - 1);
    sort(arr, pivot + 1, right);
}

void quickSort(int* arr, int length) {
    sort(arr, 0, length - 1);
}