#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"

static void resize(Array* array, int newCapacity) {
    int* newData = (int*)realloc(array->data, sizeof(int) * newCapacity);
    if(newData != NULL) {
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

void addElement(Array* array, int index, int e) {
    assert(index >= 0 && index <= array->size);
    if (array->size == array->capacity) {
        resize(array, array->capacity * 2);
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
        resize(array, array->capacity / 2);
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
    printf("Array: size = %d, capacity = %d\n", array->size, array->capacity);
    printf("[");
    for (int i = 0; i < array->size; i++) {
        printf("%d", array->data[i]);
        if (i != array->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}