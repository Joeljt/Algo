#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

// 定义加权图的顶点
typedef struct WeightedVertex {
    int vertex;
    int weight;
    struct WeightedVertex* next;
} WeightedVertex;

// 定义加权图
typedef struct WeightedGraph {
    int V;
    int E;
    int capacity;
    WeightedVertex** vertices; // 邻接表数组，每个顶点都是个链表
} WeightedGraph;

WeightedGraph* wg_create(int capacity);
void wg_destroy(WeightedGraph* graph);

int wg_addVertex(WeightedGraph* graph);
void wg_addEdge(WeightedGraph* graph, int v, int w, int weight);
WeightedVertex* wg_adj(WeightedGraph* graph, int v, int* length);

void wg_print(WeightedGraph* graph);

#endif
