#include "adj/arr_graph.h"
#include "adj/list_graph.h"
#include "mst/weighted_graph.h"
#include "mst/kruskal.h"
void test_matrix_graph() {
  MatrixGraph* graph = mg_create(5);

  for (int i = 0; i < 5; i++) {
    mg_addVertex(graph);
  }

  mg_addEdge(graph, 0, 1);
  mg_addEdge(graph, 0, 2);
  mg_addEdge(graph, 1, 2);
  mg_addEdge(graph, 1, 3);
  mg_addEdge(graph, 2, 3);
  mg_addEdge(graph, 3, 4);

  mg_print(graph);

  AdjMatrix list = mg_adj(graph, 0);
  printf("Adjacent vertices of 0: ");
  for (int i = 0; i < list.count; i++) {
    printf("%d ", list.neighbours[i]);
  }
  printf("\n");

  mg_destroy(graph);
}

void test_list_graph() {
  ListGraph* graph = lg_create(7);

  for (int i = 0; i < 7; i++) {
    lg_addVertex(graph);
  }

  lg_addEdge(graph, 5, 6);
  lg_addEdge(graph, 2, 6);
  lg_addEdge(graph, 2, 3);
  lg_addEdge(graph, 1, 4);
  lg_addEdge(graph, 1, 3); 
  lg_addEdge(graph, 0, 2);
  lg_addEdge(graph, 0, 1);

  // 破坏二分图性质
  lg_addEdge(graph, 1, 2);

  AdjList list = lg_adj(graph, 0);
  printf("Adjacent vertices of 0: ");
  for (int i = 0; i < list.count; i++) {
    printf("%d ", list.neighbours[i]);
  }
  printf("\n");

  lg_dfs(graph);
  printf("2->4: %d\n", lg_isConnected(graph, 2, 4));

  int len = 0;
  int* path = lg_path(graph, 0, 6, &len);
  printf("\n0->6 path: ");
  for (int i = 0; i < len; i++) {
    printf("%d ", path[i]);
  }
  printf("\n");

  printf("是否有环：%d\n", lg_hasCycle(graph));
  printf("是否是二分图：%d\n", lg_isBipartite(graph));

  lg_bfs(graph);
  int length = 0;
  int* pathbfs = lg_path_bfs(graph, 0, 6, &length);
  printf("\n0->6 path: ");
  for (int i = 0; i < length; i++) {
    printf("%d ", pathbfs[i]);
  }
  printf("\n"); 
  printf("是否有环：%d\n", lg_hasCycle_bfs(graph));
  printf("是否是二分图：%d\n", lg_isBipartite_bfs(graph));

  lg_destroy(graph);
}

void test_weighted_graph() {
  // 创建一个容量为5的图
  WeightedGraph* graph = wg_create(5);
  
  // 添加5个顶点
  for(int i = 0; i < 5; i++) {
      wg_addVertex(graph);
  }
  
  // 添加一些带权边
  wg_addEdge(graph, 0, 1, 2);  // 0-1 权重为2
  wg_addEdge(graph, 0, 2, 3);  // 0-2 权重为3
  wg_addEdge(graph, 1, 2, 1);  // 1-2 权重为1
  wg_addEdge(graph, 1, 3, 4);  // 1-3 权重为4
  wg_addEdge(graph, 2, 3, 5);  // 2-3 权重为5
  
  wg_print(graph);

  wg_destroy(graph);
}

void test_kruskal() {
  WeightedGraph* graph = wg_create(7);
  for (int i = 0; i < 7; i++) {
    wg_addVertex(graph);
  }

  wg_addEdge(graph, 4, 6, 7);
  wg_addEdge(graph, 3, 6, 5);
  wg_addEdge(graph, 3, 4, 1);
  wg_addEdge(graph, 2, 5, 4);
  wg_addEdge(graph, 2, 4, 4);
  wg_addEdge(graph, 1, 5, 5);
  wg_addEdge(graph, 1, 4, 3);
  wg_addEdge(graph, 1, 3, 4);
  wg_addEdge(graph, 1, 2, 1);
  wg_addEdge(graph, 0, 5, 2);
  wg_addEdge(graph, 0, 3, 7);
  wg_addEdge(graph, 0, 1, 2);
 
  // wg_print(graph);

  int length = 0;
  KEdge* mst = kruskal(graph, &length);
  for (int i = 0; i < length; i++) {
    printf("%d-%d: %d\n", mst[i].v, mst[i].w, mst[i].weight);
  }
  wg_destroy(graph);
}

#ifdef TEST_GRAPH
int main() {
  // test_matrix_graph();
  // printf("\n");
  // test_list_graph();
  // printf("\n");
  // test_weighted_graph();
  test_kruskal();
  return 0;
}
#endif