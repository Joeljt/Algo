#ifdef TEST_MST
#include "prim/pq_prim.h"
#include "prim/prim.h"
#include "kruskal/kruskal.h"

// 测试用例1：简单的连通图
/*
    2       3
  0 --- 1 --- 2
  |     |     |
  4 --- 3 --- 5
    6       1
*/
void test_simple_connected() {
    WeightedGraph* g = wg_create(6);
    for(int i = 0; i < 6; i++) wg_addVertex(g);
    
    wg_addEdge(g, 0, 1, 2);  // 0-1 权重2
    wg_addEdge(g, 1, 2, 3);  // 1-2 权重3
    wg_addEdge(g, 0, 3, 4);  // 0-3 权重4
    wg_addEdge(g, 1, 3, 5);  // 1-3 权重5
    wg_addEdge(g, 2, 5, 1);  // 2-5 权重1
    wg_addEdge(g, 3, 5, 1);  // 3-5 权重1
    wg_addEdge(g, 3, 4, 6);  // 3-4 权重6
    
    int length = 0;
    PEdge* mst = prim(g, &length);
    
    // 验证结果
    assert(length == 5);  // 应该有5条边
    for (int i = 0; i < length; i++) {
        printf("(%d, %d, %d)\n", mst[i].v, mst[i].w, mst[i].weight);
    }
    
    free(mst);
    wg_destroy(g);
}

// 测试用例2：不连通图
/*
  0 --- 1    2 --- 3
*/
void test_disconnected() {
    WeightedGraph* g = wg_create(4);
    for(int i = 0; i < 4; i++) wg_addVertex(g);
    
    wg_addEdge(g, 0, 1, 1);
    wg_addEdge(g, 2, 3, 1);
    
    int length;
    PEdge* mst = prim(g, &length);
    
    assert(length == -1);  // 应该返回-1表示图不连通
    assert(mst == NULL);   // 应该返回NULL
    
    wg_destroy(g);
}

// 测试用例3：有相同权重的边
/*
    1       1
  0 --- 1 --- 2
  |     |     |
  1     1     1
  |     |     |
  3 --- 4 --- 5
    1       1
*/
void test_same_weights() {
    WeightedGraph* g = wg_create(6);
    for(int i = 0; i < 6; i++) wg_addVertex(g);
    
    wg_addEdge(g, 0, 1, 1);
    wg_addEdge(g, 1, 2, 1);
    wg_addEdge(g, 0, 3, 1);
    wg_addEdge(g, 1, 4, 1);
    wg_addEdge(g, 2, 5, 1);
    wg_addEdge(g, 3, 4, 1);
    wg_addEdge(g, 4, 5, 1);
    
    int length;
    PEdge* mst = prim(g, &length);
    
    assert(length == 5);  // 应该有5条边
    // 所有边的权重都应该是1
    
    free(mst);
    wg_destroy(g);
}

void test_pq_prim() {
    WeightedGraph* g = wg_create(6);
    for(int i = 0; i < 6; i++) wg_addVertex(g);
    
    wg_addEdge(g, 0, 1, 2);  // 0-1 权重2
    wg_addEdge(g, 1, 2, 3);  // 1-2 权重3
    wg_addEdge(g, 0, 3, 4);  // 0-3 权重4
    wg_addEdge(g, 1, 3, 5);  // 1-3 权重5
    wg_addEdge(g, 2, 5, 1);  // 2-5 权重1
    wg_addEdge(g, 3, 5, 1);  // 3-5 权重1
    wg_addEdge(g, 3, 4, 6);  // 3-4 权重6

    int length = 0;
    PQEdge* mst = pq_prim(g, &length);

    for (int i = 0; i < length; i++) {
        printf("(%d, %d, %d)\n", mst[i].v, mst[i].w, mst[i].weight);
    }

    free(mst);
    wg_destroy(g);
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


int main() {
  printf("kruskal\n");
  test_kruskal();
  printf("prim\n");
  test_simple_connected();
  // test_disconnected();
  // test_same_weights();
  // printf("All tests passed!\n");

  printf("pq_prim\n");
  test_pq_prim();

  return 0;
}
#endif
