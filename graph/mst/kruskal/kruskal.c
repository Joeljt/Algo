#include "kruskal.h"

static int compareEdges(const void* a, const void* b) {
    return ((KEdge*)a)->weight - ((KEdge*)b)->weight;
}

KEdge* kruskal(WeightedGraph* graph, int* length) {

    // 如果图中存在多个联通分量，可以直接返回，这样的图不存在最小生成树
    // assert(graph->ccCount > 1);

    KEdge* mst = (KEdge*)malloc((graph->V - 1) * sizeof(KEdge));
    KEdge* allEdges = (KEdge*)malloc(graph->E * sizeof(KEdge));

    // 遍历所有顶点，收集边
    int edgeCount = 0;
    for (int v = 0; v < graph->V; v++) {
        // 获取所有与当前顶点相连的顶点
        WeightedVertex* current = graph->vertices[v];
        while (current != NULL) {
            // 无向图只需要判断一半即可，0-1 和 1-0 是同一条边
            if (v < current->vertex) {
                allEdges[edgeCount].v = v;
                // current->vertex 就是与 v 顶点相连接的顶点
                allEdges[edgeCount].w = current->vertex;
                allEdges[edgeCount].weight = current->weight;
                // 更新边总数
                edgeCount = edgeCount + 1;
            }
            current = current->next;
        }
    }
    // 将所有边按照权重进行排序
    qsort(allEdges, edgeCount, sizeof(KEdge), compareEdges);

    // 从小到大遍历所有边，两端顶点不在同一个联通分量中的边一定属于最小生成树
    RankQuickUnion* qu = qu_rank_create(graph->V);

    int mstCount = 0;
    for (int i = 0; i < edgeCount; i++) {
        if (!qu_rank_connected(qu, allEdges[i].v, allEdges[i].w)) {
            // 将当前边加入到最小生成树中
            mst[mstCount].v = allEdges[i].v;
            mst[mstCount].w = allEdges[i].w;
            mst[mstCount].weight = allEdges[i].weight;
            mstCount = mstCount + 1;
            // 将当前边两端的顶点合并到同一个联通分量中
            qu_rank_union(qu, allEdges[i].v, allEdges[i].w);
        }
    }
    qu_rank_destroy(qu);
    free(allEdges);
    *length = mstCount;
    
    return mst;
}