#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
// 基础数组操作
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// 数组生成函数
int* generateRandomArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr) return NULL;

    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }
    return arr;
}

int* generateSortedArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr) return NULL;

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

int* generateReversedArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr) return NULL;

    for (int i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}

int* generateNearlySortedArray(int size, int swapCount) {
    int* arr = generateSortedArray(size);
    if (!arr) return NULL;

    for (int i = 0; i < swapCount; i++) {
        int pos1 = rand() % size;
        int pos2 = rand() % size;
        swap(&arr[pos1], &arr[pos2]);
    }
    return arr;
}

// 验证函数
bool isSorted(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

bool arrayEquals(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

// 性能测试
SortStats* measureSort(void (*sortFunc)(int*, int), int* arr, int size) {
    SortStats* stats = (SortStats*)malloc(sizeof(SortStats));
    if (!stats) return NULL;

    clock_t start = clock();
    sortFunc(arr, size);
    clock_t end = clock();

    stats->timeInMs = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
    // 注意：comparisons 和 swaps 需要在排序算法内部统计
    stats->comparisons = 0;  
    stats->swaps = 0;

    assert(isSorted(arr, size));

    return stats;
}

void printSortStats(const char* sortName, SortStats* stats) {
    printf("=== %s ===\n", sortName);
    printf("执行时间: %.2f ms\n", stats->timeInMs);
    printf("比较次数: %ld\n", stats->comparisons);
    printf("交换次数: %ld\n", stats->swaps);
    printf("==================\n");
}

// 数组工具函数
int* copyArray(int* arr, int size) {
    int* copy = (int*)malloc(size * sizeof(int));
    if (copy) {
        memcpy(copy, arr, size * sizeof(int));
    }
    return copy;
}

void freeArray(int* arr) {
    free(arr);
}