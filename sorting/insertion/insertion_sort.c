#include "insertion_sort.h"

void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int target = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > target) {
            arr[j] = arr[j - 1];
            j--;
        } 
        arr[j] = target;
    }
}