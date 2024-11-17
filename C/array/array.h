# pragma once

#ifndef ARRAY_H
#define ARRAY_H

// Opague type
typedef struct Array Array;

Array* createArray(int capacity);
void destroyArray(Array* array);

int getSize(Array* array);
int getCapacity(Array* array);
int isEmpty(Array* array);

void addElement(Array* array, int index, int e);
void addLast(Array* array, int e);
void addFirst(Array* array, int e);

int removeElement(Array* array, int index);
int removeFirst(Array* array);
int removeLast(Array* array);

void printArray(Array* array);

#endif