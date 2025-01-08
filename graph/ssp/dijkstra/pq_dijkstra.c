#include "pq_dijkstra.h"

typedef struct Path {
  int vertex;
  int weight;
} Path;

int compare(void* v, void* w) {
  return ((Path*)w)->weight - ((Path*)v)->weight;
}

void pq_dijkstra_print(int* distTo, int* from, int end, char* result) {
  result[0] = '\0';  
  char temp[50];  
  int curr = end;
  while (curr != -1) {
      sprintf(temp, "%d(%d)", curr, distTo[curr]);
      strcat(result, temp);
      curr = from[curr];
      if (curr != -1) {
          strcat(result, " -> ");
      }
  }
}

void pq_dijkstra(WeightedGraph* g, int s, char* result) {

  // 初始化 distTo 数组，存储对应顶点的最短路径长度
  int* distTo = (int*)malloc(g->V * sizeof(int));
  for (int i = 0; i < g->V; i++) {
      distTo[i] = INT_MAX;
  }
  distTo[s] = 0;

  // 初始化 visited 数组，用来标记是否确定了对应顶点的最短路径
  // 所有值都初始化为 0，表示没有访问过任何顶点
  int* visited = (int*)malloc(g->V * sizeof(int));
  memset(visited, 0, g->V * sizeof(int));

  // 初始化 from 数组，用来记录具体的路径信息
  // 填充 -1 表示未访问
  int* from = (int*)malloc(g->V * sizeof(int));
  memset(from, -1, g->V * sizeof(int));

  PriorityQueue* pq = pq_create(g->V, compare);

  // 把起点加入优先队列
  Path* start = (Path*)malloc(sizeof(Path));
  start->vertex = s;
  start->weight = 0;
  pq_push(pq, start);

  while (!pq_is_empty(pq)) {
    // 取出当前队列中距离最小的那个顶点，即 minV，是当前能确定最短路径的顶点
    Path* min = (Path*)pq_pop(pq);
    int minV = min->vertex;

    // 标记该顶点访问状态，确定其最短路径
    visited[minV] = 1;

    // 遍历与 minV 相连的所有顶点
    int length = 0;
    WeightedVertex* vertices = wg_adj(g, minV, &length);
    for (int i = 0; i < length; i++) {
      WeightedVertex wv = vertices[i];

      // 检查根据当前这个新得到的顶点的最短路径，能不能更新之前的路径信息
      if (!visited[wv.vertex] && distTo[minV] + wv.weight < distTo[wv.vertex]) {
        // 如果新算出来的结果比之前的记录还要小，就要更新 distTo 的信息
        distTo[wv.vertex] = distTo[minV] + wv.weight;
        // 记录路径
        from[wv.vertex] = minV;

        // 把当前顶点和最新的距离信息组装加入队列
        Path* path = (Path*)malloc(sizeof(Path));
        path->vertex = wv.vertex;
        path->weight = distTo[wv.vertex];
        pq_push(pq, path);
      }
    }
    free(min);
    free(vertices);
  }
  pq_destroy(pq);

  pq_dijkstra_print(distTo, from, g->V - 1, result);

  free(distTo);
  free(visited);
  free(from);
}