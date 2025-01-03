#ifndef __ARR_GRAPH_H__
#define __ARR_GRAPH_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 定义相邻节点的结构信息
typedef struct {
  int* neighbours;
  int count;
} AdjMatrixList;

// 定义图结构
typedef struct {
  int V;
  int E;
  int capacity;
  int** adj;
} MatrixGraph;

MatrixGraph* mg_create(int capacity);
void mg_destroy(MatrixGraph* graph);

int mg_addVertex(MatrixGraph* graph);
void mg_addEdge(MatrixGraph* graph, int a, int b);
AdjMatrixList mg_adj(MatrixGraph* graph, int v);

void mg_print(MatrixGraph* graph);

#endif