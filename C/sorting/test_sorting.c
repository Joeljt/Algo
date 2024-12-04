#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "helper.h"
#include "bubble/bubble_sort.h"
#include "shell/shell_sort.h"
#include "merge/merge_sort.h"
#include "insert/insertion_sort.h"
#include "select/selection_sort.h"
#include "quick/quick_sort.h"

#define ARRAY_SIZE 100000

int main() {

    int* arr = generateRandomArray(ARRAY_SIZE);

    // 插入排序
    int* arr1 = copyArray(arr, ARRAY_SIZE);
    measureSort("插入排序", insertionSort, arr1, ARRAY_SIZE);
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
    // measureSort("快速排序", quickSort, arr5, ARRAY_SIZE);
    freeArray(arr5);

    // 冒泡排序
    int* arr6 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序", bubbleSort, arr6, ARRAY_SIZE);
    freeArray(arr6);

    int* arr7 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序2", bubbleSort2, arr7, ARRAY_SIZE);
    freeArray(arr7);

    int* arr8 = copyArray(arr, ARRAY_SIZE);
    // measureSort("冒泡排序3", bubbleSort3, arr8, ARRAY_SIZE);
    freeArray(arr8);

    int* arr9 = copyArray(arr, ARRAY_SIZE);
    measureSort("希尔排序", shellSort, arr9, ARRAY_SIZE);
    freeArray(arr9);

    int* arr10 = copyArray(arr, ARRAY_SIZE);
    measureSort("希尔排序2", shellSort2, arr10, ARRAY_SIZE);
    freeArray(arr10);

    freeArray(arr);

    return 0;
}