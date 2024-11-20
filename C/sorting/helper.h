#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>  // 为了使用 bool 类型

// 数组操作
void swap(int* a, int* b);
void printArray(int* arr, int size);

// 数组生成
int* generateRandomArray(int size);
int* generateSortedArray(int size);
int* generateReversedArray(int size);
int* generateNearlySortedArray(int size, int swapCount);

// 数组验证
bool isSorted(int* arr, int size);
bool arrayEquals(int* arr1, int* arr2, int size);

// 性能测试
typedef struct {
    double timeInMs;      // 执行时间（毫秒）
    long comparisons;     // 比较次数
    long swaps;          // 交换次数
} SortStats;

SortStats* measureSort(void (*sortFunc)(int*, int), int* arr, int size);
void printSortStats(const char* sortName, SortStats* stats);

// 数组复制和释放
int* copyArray(int* arr, int size);
void freeArray(int* arr);

#endif