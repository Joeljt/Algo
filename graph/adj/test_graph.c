#include "arr_graph.h"
#include "list_graph.h"

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
  ListGraph* graph = lg_create(5);

  for (int i = 0; i < 5; i++) {
    lg_addVertex(graph);
  }

  lg_addEdge(graph, 2, 0);
  lg_addEdge(graph, 2, 3);
  lg_addEdge(graph, 0, 1);
  lg_addEdge(graph, 3, 4);
  lg_addEdge(graph, 4, 0);
  // lg_addEdge(graph, 1, 2);
  lg_print(graph);

  AdjList list = lg_adj(graph, 0);
  printf("Adjacent vertices of 0: ");
  for (int i = 0; i < list.count; i++) {
    printf("%d ", list.neighbours[i]);
  }
  printf("\n");

  lg_dfs(graph);
  printf("2->4: %d\n", lg_isConnected(graph, 2, 4));

  int len = 0;
  int* path = lg_path(graph, 1, 3, &len);
  printf("\n2->1 path: ");
  for (int i = 0; i < len; i++) {
    printf("%d ", path[i]);
  }
  printf("\n");

  printf("是否有环：%d\n", lg_hasCycle(graph));
  printf("是否是二分图：%d\n", lg_isBipartite(graph));

  lg_destroy(graph);
}

#ifdef TEST_GRAPH
int main() {
  test_matrix_graph();
  printf("\n");
  test_list_graph();
  return 0;
}
#endif