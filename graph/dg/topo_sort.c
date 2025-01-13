#include "topo_sort.h"

int* topo_sort(DirectedGraph* g, int* length) {

    int* result = (int*)malloc(g->V * sizeof(int));
    
    CircularQueue* queue = cq_create(g->V);
    for (int i = 0; i < g->V; i++) {
      if (g->indegree[i] == 0) cq_enqueue(queue, i);
    }

    int index = 0;
    while (!cq_isEmpty(queue)) {
      // 取出队列中的顶点，应该是入度为 0 的顶点
      int vertex = cq_dequeue(queue);

      // 将当前顶点加入到结果中
      result[index++] = vertex;

      // 遍历该顶点的所有相邻顶点，将该顶点的入度 -1，表示其依赖顶点已被访问
      int len = 0;
      DEdge* edges = dg_adj(g, vertex, &len);
      for (int i = 0; i < len; i++) {
        int v = edges[i].vertex;
        // 更新当前顶点的入度信息
        g->indegree[v] = g->indegree[v] - 1;
        // 将最新找到的入度为 0 的顶点加入队列
        if (g->indegree[v] == 0) {
          cq_enqueue(queue, v);
        }
      }
      free(edges);
    }
    cq_destroy(queue);

    if (g->V == 0 || index != g->V) {
      free(result);
      *length = -1;
      return NULL;
    }

    *length = index;
    return result;
}

void dfs(DirectedGraph* g, int v, int* result, int* index) {
  g->visited[v] = 1;
  
  // 遍历当前顶点的所有相邻顶点
  int len = 0;
  DEdge* edges = dg_adj(g, v, &len);
  for (int i = 0; i < len; i++) {
    int next = edges[i].vertex;
    // 如果相邻顶点未访问，则继续向下遍历
    if (!g->visited[next]) {
      dfs(g, next, result, index);
    }
  }
  free(edges);

  // 后序遍历，将当前顶点加入到结果中
  result[(*index)++] = v;
}

int* topo_sort_dfs(DirectedGraph* g, int* length) {

  for (int i = 0; i < g->V; i++) {
    g->visited[i] = 0;
    g->onPath[i] = 0;
  }

  // 如果存在环，则无法进行拓扑排序，返回 NULL
  if (dg_hasCycle(g)) {
    *length = -1;
    return NULL;
  }

  int* result = (int*)malloc(g->V * sizeof(int));
  int index = 0;

  // dfs 遍历所有顶点，在过程中进行后序遍历，并将结果存在 result 中
  for (int i = 0; i < g->V; i++) g->visited[i] = 0;
  for (int i = 0; i < g->V; i++) {
    if (!g->visited[i]) {
      dfs(g, i, result, &index);
    }
  }

  // 将后序遍历的结果反转，即为拓扑排序的结果
  for (int i = 0; i < g->V / 2; i++) {
    int temp = result[i];
    result[i] = result[g->V - i - 1];
    result[g->V - i - 1] = temp;
  }

  *length = g->V;
  return result;
}