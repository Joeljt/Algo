#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct AdjMatrix {
    int **matrix; // 使用二维数组来表示各点之间的关系
    int size; // 一共有多少个顶点
} AdjMatrix;

AdjMatrix* am_create(int size);
void am_destroy(AdjMatrix* matrix);

void am_add_edge(AdjMatrix* matrix, int src, int dest);
void am_remove_edge(AdjMatrix* matrix, int src, int dest);
bool am_has_edge(AdjMatrix* matrix, int src, int dest);

void am_print(AdjMatrix* matrix);

#endif