#include "sorting.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int size[2] = {10000, 100000};
    for (int i = 0; i < 2; i++) {
        // 生成随机数组
        int* arr = generateRandomArray(size[i]);
        int* arr2 = copyArray(arr, size[i]);

        // 测试排序
        SortStats* stats = measureSort(selectionSort, arr, size[i]);
        
        printSortStats("选择排序", stats);

        // 测试排序
        stats = measureSort(insertionSort, arr2, size[i]);
        printSortStats("插入排序", stats);

        // 清理内存
        freeArray(arr);
        freeArray(arr2);
        free(stats);
    }

    return 0;
}