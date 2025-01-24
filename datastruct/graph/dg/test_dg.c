#ifdef TEST_DG

#include "directed_graph.h"
#include "topo_sort.h"
#include "cycle/cycle_detection.h"

void test_topo_sort(int algorithm) {
    // 测试用例1：正常的 DAG
    /*
        0 --> 1 --> 3
        |     |     ^
        v     v     |
        2 ----+-----+
    */
    {
        DirectedGraph* g1 = dg_create(4, 1);
        dg_addEdge(g1, 0, 1, 1);  // 0 -> 1
        dg_addEdge(g1, 0, 2, 1);  // 0 -> 2
        dg_addEdge(g1, 1, 3, 1);  // 1 -> 3
        dg_addEdge(g1, 2, 3, 1);  // 2 -> 3

        int length = 0;
        int* result = NULL;
        if (algorithm == 1) {
            result = topo_sort_dfs(g1, &length);
        } else {
            result = topo_sort(g1, &length);
        }
        
        printf("Normal DAG:\n");
        if (result) {
            printf("Length: %d\nOrder: ", length);
            for (int i = 0; i < length; i++) {
                printf("%d ", result[i]);
            }
            printf("\n");
            // 期望输出：0 1 2 3 或 0 2 1 3
            free(result);
        }
        dg_destroy(g1);
    }

    // 测试用例2：有环的图
    /*
        0 --> 1 --> 2
        ^           |
        |           v
        +---- 3 <---+
    */
    {
        DirectedGraph* g2 = dg_create(4, 1);
        dg_addEdge(g2, 0, 1, 0);  // 0 -> 1
        dg_addEdge(g2, 1, 2, 0);  // 1 -> 2
        dg_addEdge(g2, 2, 3, 0);  // 2 -> 3
        dg_addEdge(g2, 3, 0, 0);  // 3 -> 0 (creates cycle)

        int length = 0;
        int* result = NULL;
        if (algorithm == 1) {
            result = topo_sort_dfs(g2, &length);
        } else {
            result = topo_sort(g2, &length);
        }

        printf("\nGraph with cycle:\n");
        if (result == NULL && length == -1) {
            printf("Correctly detected cycle\n");
        } else {
            printf("Failed to detect cycle\n");
            free(result);
        }
        dg_destroy(g2);
    }
}

void test_cycle_detection() {
    // 测试用例1：有向无环图 (DAG)
    /*
        0 --> 1 --> 3
        |     |     
        v     v     
        2 --> 4
    */
    {
        DirectedGraph* g1 = dg_create(5, DG_DIRECTED);
        dg_addEdge(g1, 0, 1, 0);  // 0 -> 1
        dg_addEdge(g1, 0, 2, 0);  // 0 -> 2
        dg_addEdge(g1, 1, 3, 0);  // 1 -> 3
        dg_addEdge(g1, 1, 4, 0);  // 1 -> 4
        dg_addEdge(g1, 2, 4, 0);  // 2 -> 4

        printf("Test1 - DAG:\n");
        if (dg_hasCycle(g1)) {
            printf("Passed: Detected cycle in DAG\n");
        } else {
            printf("Failed: No cycle detected in DAG\n");
        }
        dg_destroy(g1);
    }

    // 测试用例2：包含自环
    /*
        0 --> 1 
        ^     |
        |     v
        +---- 2
    */
    {
        DirectedGraph* g2 = dg_create(3, DG_DIRECTED);
        dg_addEdge(g2, 0, 1, 0);  // 0 -> 1
        dg_addEdge(g2, 1, 2, 0);  // 1 -> 2
        dg_addEdge(g2, 2, 0, 0);  // 2 -> 0 (creates cycle)

        printf("\nTest2 - Graph with cycle:\n");
        if (dg_hasCycle(g2)) {
            printf("Passed: Correctly detected cycle\n");
        } else {
            printf("Failed: Did not detect cycle\n");
        }
        dg_destroy(g2);
    }

    // 测试用例3：多个不相连的环
    /*
        0 --> 1    3 --> 4
        ^     |    ^     |
        |     v    |     v
        2 <---+    5 <---+
    */
    {
        DirectedGraph* g3 = dg_create(6, DG_DIRECTED);
        // First cycle
        dg_addEdge(g3, 0, 1, 0);
        dg_addEdge(g3, 1, 2, 0);
        dg_addEdge(g3, 2, 0, 0);
        // Second cycle
        dg_addEdge(g3, 3, 4, 0);
        dg_addEdge(g3, 4, 5, 0);
        dg_addEdge(g3, 5, 3, 0);

        printf("\nTest3 - Multiple cycles:\n");
        if (dg_hasCycle2(g3)) {
            printf("Passed: Correctly detected cycles\n");
        } else {
            printf("Failed: Did not detect cycles\n");
        }
        dg_destroy(g3);
    }

    // 测试用例4：单个顶点的自环
    /*
        0 --> 0
    */
    {
        DirectedGraph* g4 = dg_create(1, DG_DIRECTED);
        dg_addEdge(g4, 0, 0, 0);  // Self loop

        printf("\nTest4 - Self loop:\n");
        if (dg_hasCycle2(g4)) {
            printf("Passed: Correctly detected self loop\n");
        } else {
            printf("Failed: Did not detect self loop\n");
        }
        dg_destroy(g4);
    }
}

int main() {
    printf("Test Topo Sort:\n");
    test_topo_sort(0);
    printf("\n\n");
    printf("Test Topo Sort DFS:\n");
    test_topo_sort(1);
    printf("\n\n");

    printf("Test Cycle Detection:\n");
    test_cycle_detection();
    return 0;
}
#endif