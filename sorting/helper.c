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
void measureSort(const char* sortName, void (*sort)(int*, int), int* arr, int size) {
    clock_t start = clock();
    sort(arr, size);
    clock_t end = clock();

    double timeInSec = (double)(end - start) / CLOCKS_PER_SEC;

    assert(isSorted(arr, size));

    printf("[%s] time: %.5fs, size: %d\n", sortName, timeInSec, size);

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