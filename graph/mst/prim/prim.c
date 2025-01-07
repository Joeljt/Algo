#include "prim.h"

PEdge* prim(WeightedGraph* graph, int* length) {

    PEdge* mst = (PEdge*)malloc((graph->V - 1) * sizeof(PEdge));
    int mstCount = 0;

    // 维护 visited 数组，用来标记切分
    int* visited = (int*)malloc(graph->V * sizeof(int));
    for(int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // 从 0 开始
    visited[0] = 1;

    // 遍历 V-1 次，找到 V-1 条边，构建最小生成树
    while (mstCount < graph->V - 1) {  // 最多需要 V-1 条边

        PEdge minEdge = {-1, -1, INT_MAX};

        // 遍历所有顶点，找到划分到切分的顶点
        for (int v = 0; v < graph->V; v++) {
            // 默认情况下，只要 visited[0] 是 1，其他顶点都是 0
            // 等扩大切分后，visited 中为 1 的值会越来越多，minEdge 一定会被更新为最新的那个顶点的相邻边
            // 但是过程中执行有很多浪费，会频繁重复遍历已经遍历过的顶点，而且结果会被后面遍历的顶点覆盖掉
            if (visited[v]) {
                // i 已经访问过，接下来寻找所有与 i 相邻，但是还没有被访问的顶点
                // 这两个顶点的边就是横切边
                int length = 0;
                WeightedVertex* vertices = wg_adj(graph, v, &length);
                for (int j = 0; j < length; j++) {
                    WeightedVertex adjV = vertices[j];
                    // v 和 w 需要一个访问过，另一个没有访问过，当前这条边才是横切边
                    if (!visited[adjV.vertex]) { // 找到一个横切边
                        if (adjV.weight < minEdge.weight) {
                            // 更新最小边
                            minEdge.v = v;
                            minEdge.w = adjV.vertex;
                            minEdge.weight = adjV.weight;
                        }
                    }
                }
                free(vertices);
            }
        }

        // 如果遍历完所有顶点后，minEdge 仍然为 -1，说明不再有最短横切边了
        // 要么是完成了 MST 的查找，要么是图不连通，可以中断循环
        if (minEdge.weight == INT_MAX) {
            break;
        }

        // 循环完毕后，就找到了最短的横切边，扩大切分
        visited[minEdge.w] = true;

        // 加入到 mst 中
        mst[mstCount++] = minEdge;
    }

    // 检查图是否连通
    if (mstCount != graph->V - 1) {
        *length = -1;
        free(mst);
        free(visited);
        return NULL;
    }

    // 更新 length 并返回 mst
    *length = mstCount;
    return mst;
}
