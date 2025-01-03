#include "arr_graph.h"

int main() {
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

  AdjMatrixList list = mg_adj(graph, 0);
  printf("Adjacent vertices of 0: ");
  for (int i = 0; i < list.count; i++) {
    printf("%d ", list.neighbours[i]);
  }
  printf("\n");

  mg_destroy(graph);
  return 0;
}