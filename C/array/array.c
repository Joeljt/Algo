#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"

struct Array {
    int* data;
    int size;
    int capacity;
};

// resize 方法更推荐的实践
// realloc 会直接在原内存块上进行扩展，并在必要时自动处理数据复制和原内存释放的问题
// realloc(NULL, new_size) 等价于 mallc()
// realloc(ptr, 0) 等价于 free(ptr)
static void expand(Array* array, int newCapacity) {
    int* newData = (int*)realloc(array->data, sizeof(int) * newCapacity);
    if(newData != NULL) {
        array->data = newData;
        array->capacity = newCapacity;
    }
}

// 重新申请内存空间并自己处理复制、内存释放等操作
// 性能不好，而且 array->data 的释放容易落下，更推荐 realloc 的做法
// 这里只是记录一下这种方式也可行
static void shrink(Array* array, int newCapacity) {
    int *newData = (int*)malloc(sizeof(int) * newCapacity);
    if (newData != NULL) {
        for (int i = 0; i < array->size; i++) {
            newData[i] = array->data[i];
        }
        free(array->data);
        array->data = newData;
        array->capacity = newCapacity; 
    }
}

Array* createArray(int capacity) {
    Array* array = (Array*)malloc(sizeof(Array));
    if (array == NULL) return NULL;
    array->data = (int*)malloc(sizeof(int) * capacity);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void destroyArray(Array* array) {
    free(array->data);
    free(array);
}

int getSize(Array* array) {
    return array->size;
}

int getCapacity(Array* array) {
    return array->capacity;
}

int isEmpty(Array* array) {
    return array->size == 0;
}

int getElement(Array* array, int index) {
    assert(index >= 0 && index < array->size);
    return array->data[index];
}

void addElement(Array* array, int index, int e) {
    assert(index >= 0 && index <= array->size);
    if (array->size == array->capacity) {
        expand(array, array->capacity * 2);
    }
    for (int i = array->size - 1; i >= index; i--) {
        array->data[i + 1] = array->data[i];
    }
    array->data[index] = e;
    array->size++;  
}

void addLast(Array* array, int e) {
    addElement(array, array->size, e);
}

void addFirst(Array* array, int e) {
    addElement(array, 0, e);
}

int removeElement(Array* array, int index) {
    assert(index >= 0 && index < array->size);
    int e = array->data[index];
    for (int i = index + 1; i < array->size; i++) {
        array->data[i - 1] = array->data[i];
    }
    array->size--;
    if (array->size == array->capacity / 4 && array->capacity / 2 != 0) {
        shrink(array, array->capacity / 2);
    }
    return e;
} 

int removeFirst(Array* array) {
    return removeElement(array, 0);
}

int removeLast(Array* array) {
    return removeElement(array, array->size - 1);
}

void printArray(Array* array) {
    printf("Array: (%d/%d)\n", array->size, array->capacity);
    printf("[");
    for (int i = 0; i < array->size; i++) {
        printf("%d", array->data[i]);
        if (i != array->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}