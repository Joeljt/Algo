#include "directed_graph.h"

DirectedGraph* dg_create(int V, int directed) {
    DirectedGraph* g = (DirectedGraph*)malloc(sizeof(DirectedGraph));
    g->V = V;
    g->E = 0;
    g->directed = directed;
    g->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
          // 自己到自己（对角线）为 0，其他默认没有边，初始化为 INF
            g->matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
    // 初始化入度、出度都为 0
    g->indegree = (int*)malloc(V * sizeof(int));
    g->outdegree = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        g->indegree[i] = 0;
        g->outdegree[i] = 0;
    }
    g->visitState = (int*)malloc(V * sizeof(int));
    g->visited = (int*)malloc(V * sizeof(int));
    g->onPath = (int*)malloc(V * sizeof(int));
    return g;
}

void dg_destroy(DirectedGraph* g) {
    for (int i = 0; i < g->V; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

void dg_addEdge(DirectedGraph* g, int u, int v, int weight) {
    assert(u >= 0 && u < g->V && v >= 0 && v < g->V);
    g->matrix[u][v] = weight;
    // 维护入度和出度信息
    g->outdegree[u]++;
    g->indegree[v]++;
    if (!g->directed) {
        g->matrix[v][u] = weight;
        // 无向图需要维护两个方向的入度和出度
        g->outdegree[v]++;
        g->indegree[u]++;
    }
    g->E++;
}

DEdge* dg_adj(DirectedGraph* g, int v, int* length) {
    assert(v >= 0 && v < g->V);
    // 返回顶点 v 的邻接表
    DEdge* edges = (DEdge*)malloc(g->V * sizeof(DEdge));
    int count = 0;
    for (int i = 0; i < g->V; i++) {
        if (g->matrix[v][i] != INF) {
            edges[count].vertex = i;
            edges[count].weight = g->matrix[v][i];
            count++;
        }
    }
    // 将返回的列表重新调整为实际的大小
    edges = (DEdge*)realloc(edges, count * sizeof(DEdge));
    // 更新实际的长度
    *length = count;
    return edges;
}

void dg_print(DirectedGraph* g) {
    printf("\nDirected Graph:\n");
    for (int i = 0; i < g->V; i++) {
        printf("%d: ", i);
        for (int j = 0; j < g->V; j++) {
          printf("%d ", g->matrix[i][j] != INF ? g->matrix[i][j] : 0);
        }
        printf("\n");
    }
}