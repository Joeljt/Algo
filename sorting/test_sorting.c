#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "helper.h"
#include "bubble/bubble_sort.h"
#include "shell/shell_sort.h"
#include "merge/merge_sort.h"
#include "insertion/insertion_sort.h"
#include "selection/selection_sort.h"
#include "quick/quick_sort.h"
#include "heap/heap_sort.h"

#define ARRAY_SIZE 1000000

#ifdef TEST_SORTING
int main() {

    int* arr = generateRandomArray(ARRAY_SIZE);

    // 插入排序
    int* arr1 = copyArray(arr, ARRAY_SIZE);
    // measureSort("插入排序", insertionSort, arr1, ARRAY_SIZE);
    freeArray(arr1);

    // 选择排序
    int* arr2 = copyArray(arr, ARRAY_SIZE);
    // measureSort("选择排序", selectionSort, arr2, ARRAY_SIZE);
    freeArray(arr2);

    // 迭代归并排序
    int* arr3 = copyArray(arr, ARRAY_SIZE);
    // measureSort("迭代归并", iterativeMergeSort, arr3, ARRAY_SIZE);
    freeArray(arr3);

    // 递归归并排序
    int* arr4 = copyArray(arr, ARRAY_SIZE);
    // measureSort("递归归并", recursiveMergeSort, arr4, ARRAY_SIZE);
    freeArray(arr4);

    // 快速排序
    int* arr5 = copyArray(arr, ARRAY_SIZE);
    measureSort("快速排序", quickSort, arr5, ARRAY_SIZE);
    freeArray(arr5);

    // 冒泡排序
    int* arr6 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序", bubbleSort, arr6, ARRAY_SIZE);
    freeArray(arr6);

    int* arr7 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序1", bubbleSort1, arr7, ARRAY_SIZE);
    freeArray(arr7);

    int* arr8 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序3", bubbleSort2, arr8, ARRAY_SIZE);
    freeArray(arr8);

    int* arr9 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序3", bubbleSort3, arr9, ARRAY_SIZE);
    freeArray(arr9);

    int* arr10 = copyArray(arr, ARRAY_SIZE);
    // measureSort("希尔排序", shellSort, arr10, ARRAY_SIZE);
    freeArray(arr10);

    int* arr11 = copyArray(arr, ARRAY_SIZE);
    // measureSort("希尔排序2", shellSort2, arr11, ARRAY_SIZE);
    freeArray(arr11);

    int* arr12 = copyArray(arr, ARRAY_SIZE);
    measureSort("堆排序", heapSort, arr12, ARRAY_SIZE);
    freeArray(arr12);

    int* arr13 = copyArray(arr, ARRAY_SIZE);
    measureSort("堆排序1", heapSort1, arr13, ARRAY_SIZE);
    freeArray(arr13);

    int* arr14 = copyArray(arr, ARRAY_SIZE);
    measureSort("堆排序2", heapSort2, arr14, ARRAY_SIZE);
    freeArray(arr14);

    freeArray(arr);

    return 0;
}
#endif