#include "dijkstra/dijkstra.h"

#ifdef TEST_SSP

void test_dijkstra() {
    // 测试用例1：简单路径
    /*
        2       3
    0 --- 1 --- 2
    |     |     |
    4     5     1
    |     |     |
    3 --- 4 --- 5
        6       2
    */
    {
        WeightedGraph* g = wg_create(6);
        for(int i = 0; i < 6; i++) wg_addVertex(g);
           
        wg_addEdge(g, 0, 1, 2);  // 0-1 权重2
        wg_addEdge(g, 1, 2, 3);  // 1-2 权重3
        wg_addEdge(g, 0, 3, 4);  // 0-3 权重4
        wg_addEdge(g, 1, 4, 5);  // 1-4 权重5
        wg_addEdge(g, 2, 5, 1);  // 2-5 权重1
        wg_addEdge(g, 3, 4, 6);  // 3-4 权重6
        wg_addEdge(g, 4, 5, 2);  // 4-5 权重2

        char result[1000];
        dijkstra(g, 0, result);
        printf("Test1 - Simple path from 0 to 5:\n%s\n\n", result);
        // 期望输出：0(0) -> 1(2) -> 2(5) -> 5(6)
        
        wg_destroy(g);
    }

    // 测试用例2：最短路径不是最少边的路径
    /*
        2       10
    0 --- 1 --- 2
    |           |
    5           1
    |           |
    3 --- 4 --- 5
        1       1
    */
    {
        WeightedGraph* g = wg_create(6);
        for(int i = 0; i < 6; i++) wg_addVertex(g);
        
        wg_addEdge(g, 0, 1, 2);   // 0-1 权重2
        wg_addEdge(g, 1, 2, 10);  // 1-2 权重10
        wg_addEdge(g, 0, 3, 5);   // 0-3 权重5
        wg_addEdge(g, 2, 5, 1);   // 2-5 权重1
        wg_addEdge(g, 3, 4, 1);   // 3-4 权重1
        wg_addEdge(g, 4, 5, 1);   // 4-5 权重1

        char result[1000];
        dijkstra(g, 0, result);
        printf("Test2 - Path with fewer edges is not shortest:\n%s\n\n", result);
        // 期望输出：0(0) -> 3(5) -> 4(6) -> 5(7)
        
        wg_destroy(g);
    }

    // 测试用例3：不连通的图
    /*
    0 --- 1    2 --- 3
    */
    {
        WeightedGraph* g = wg_create(4);
        for(int i = 0; i < 4; i++) wg_addVertex(g);
        
        wg_addEdge(g, 0, 1, 1);  // 0-1 权重1
        wg_addEdge(g, 2, 3, 1);  // 2-3 权重1

        char result[1000];
        dijkstra(g, 0, result);
        printf("Test3 - Disconnected graph:\n%s", result);
        // 期望输出：无法到达
        
        wg_destroy(g);
    }
}

int main() {
    test_dijkstra();
}

#endif