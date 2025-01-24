#ifndef __DIRECTED_GRAPH_H__
#define __DIRECTED_GRAPH_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DG_DIRECTED 1
#define DG_UNDIRECTED 0
#define INF 99999

typedef struct {
    int vertex;
    int weight;
} DEdge;

typedef struct {
    int V;
    int E;
    int** matrix;
    int directed;

    int* visitState; // 记录顶点的访问状态

    int* visited; // 记录顶点的访问状态
    int* onPath; // 记录当前路径上的顶点

    int* indegree;
    int* outdegree;
} DirectedGraph;

DirectedGraph* dg_create(int V, int directed);
void dg_destroy(DirectedGraph* g);

void dg_addEdge(DirectedGraph* g, int u, int v, int weight);

DEdge* dg_adj(DirectedGraph* g, int v, int* length);

bool dg_hasCycle(DirectedGraph* g);
void dg_print(DirectedGraph* g);

#endif