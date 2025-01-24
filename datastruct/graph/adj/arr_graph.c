#include "arr_graph.h"

MatrixGraph* mg_create(int capacity) {
  MatrixGraph* graph = (MatrixGraph*)malloc(sizeof(MatrixGraph));

  // 为新申请的图初始化数据，默认情况下没有顶点也没有边
  graph->V = 0;
  graph->E = 0;
  graph->capacity = capacity;

  // 给邻接矩阵分配空间并给所有元素都初始化为 0
  // 矩阵大小为 nxn，用来表示每个顶点相对于其他顶点的连接状态
  // 1. 我们不考虑自环边，所以矩阵的对角线都为 0，即不存在 a 与 a 连接；
  // 2. 我们不考虑边的方向，所以矩阵是基于对角线对称的，即 a 与 b 连接一定代表着 b 与 a 连接；
  graph->adj = (int**)malloc(capacity * sizeof(int*));
  for (int i = 0; i < capacity; i++) {
    // 为每个节点都初始化相对于其他节点的连接状态，并初始化为 0，即默认不连接
    graph->adj[i] = (int*)malloc(capacity * sizeof(int));
    for (int j = 0; j < capacity; j++) {
      graph->adj[i][j] = 0;
    }
    // 或者直接利用 calloc 来实现同样的效果
    // graph->adj[i] = (int*)calloc(capacity, sizeof(int));
  }

  return graph;
}

void mg_destroy(MatrixGraph* graph) {
  for (int i = 0; i < graph->capacity; i++) {
    free(graph->adj[i]);
  }
  free(graph->adj);
  free(graph);
}

// 按顺序向图中添加一个顶点，不能超过最开始初始化的图大小
int mg_addVertex(MatrixGraph* graph) {
  assert(graph->V < graph->capacity);
  return graph->V++;
}

void mg_addEdge(MatrixGraph* graph, int a, int b) {
  assert((a >= 0 && a < graph->V) && (b >= 0 && b < graph->V));
  if (graph->adj[a][b] == 0) {
    // 无向图，两个节点相对于对方都需要标记连接
    graph->adj[a][b] = 1;
    graph->adj[b][a] = 1;
    // 维护 E
    graph->E++;
  }
}

// 查找顶点 v 在图中所有相连的顶点
AdjMatrix mg_adj(MatrixGraph* graph, int v) {
  assert(v >= 0 && v < graph->V);
  // 初始化一个结构，用来记录存储的相连节点列表和数量信息
  AdjMatrix result = {NULL, 0};

  // 初始化临时数组，顶点数量最大不可能超过总节点数量
  int* temp = (int*)malloc(sizeof(int) * graph->V);
  int index = 0;
  for (int i = 0; i < graph->V; i++) {
    // 在当前顶点的连接表中查找连接的顶点，并将其放到数组中记录下来
    if (graph->adj[v][i] == 1) {
      temp[index] = i;
      index++;
    }
  }
  // 将返回的列表重新调整为实际的大小
  result.neighbours = (int*)realloc(temp, index * sizeof(int));
  result.count = index;
  return result;
}

void mg_print(MatrixGraph* graph) {
  printf("Adjacency Matrix:\n");
  for (int i = 0; i < graph->V; i++) {
    for (int j = 0; j < graph->V; j++) {
      printf("%d ", graph->adj[i][j]);
    }
    printf("\n");
  }
}



