#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "helper.h"
#include "merge/merge_sort.h"
#include "insert/insertion_sort.h"
#include "select/selection_sort.h"
#include "quick/quick_sort.h"
#define ARRAY_SIZE 100000

int main() {

    int size[2] = {100000, 1000000};
    for (int i = 0; i < 2; i++) {
        int* arr = generateRandomArray(size[i]);

        // 插入排序
        int* arr1 = copyArray(arr, size[i]);
        // measureSort("插入排序", insertionSort, arr1, size[i]);
        freeArray(arr1);

        // 选择排序
        int* arr2 = copyArray(arr, size[i]);
        // measureSort("选择排序", selectionSort, arr2, size[i]);
        freeArray(arr2);

        // 迭代归并排序
        int* arr3 = copyArray(arr, size[i]);
        measureSort("迭代归并", iterativeMergeSort, arr3, size[i]);
        freeArray(arr3);

        // 递归归并排序
        int* arr4 = copyArray(arr, size[i]);
        measureSort("递归归并", recursiveMergeSort, arr4, size[i]);
        freeArray(arr4);

        // 快速排序
        int* arr5 = copyArray(arr, size[i]);
        measureSort("快速排序", quickSort, arr5, size[i]);
        freeArray(arr5);

        freeArray(arr);
    }

    return 0;
}