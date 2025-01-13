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