#include "pq_prim.h"

int compare(void* v, void* w) {
    return ((PQEdge*)w)->weight - ((PQEdge*)v)->weight;
}

PQEdge* pq_prim(WeightedGraph* graph, int* length) {

    // 最小生成树，V 个顶点需要 V - 1 条边
    PQEdge* mst = (PQEdge*)malloc((graph->V) * sizeof(PQEdge));
    int mstCount = 0;

    // 维护一个切分数组，用来记录哪些切分已经访问过，哪些没有，用来找横切边
    int* visited = (int*)malloc((graph->V) * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // 初始化最小堆，大小初始化为所有的边长
    PriorityQueue* pq = pq_create(graph->E, compare);

    // 从 0 开始，把 0 的所有邻边全部放到优先队列里
    visited[0] = true;

    int len = 0;
    WeightedVertex* vertices = (WeightedVertex*)wg_adj(graph, 0, &len);
    for (int i = 0; i < len; i++) {
        PQEdge* edge = (PQEdge*)malloc(sizeof(PQEdge));
        edge->v = 0;
        edge->w = vertices[i].vertex;
        edge->weight = vertices[i].weight;
        pq_push(pq, edge);
    }

    // 开始找横切边，只要队列还不为空，就继续
    while (!pq_is_empty(pq)) {
        PQEdge* edge = (PQEdge*)pq_pop(pq);

        // 在确定新的最短横切边时，某些之前加入到队列中的边有可能不再是横切边了
        // 具体表现就是这条边的两个顶点都访问过，直接跳过去查看下一条边
        if (visited[edge->v] && visited[edge->w]) {
            free(edge);
            continue;
        }
        
        mst[mstCount++] = *edge;

        int target = visited[edge->v] ? edge->w : edge->v;
        visited[target] = true;

        free(edge);

        int len = 0;
        WeightedVertex* vertices = (WeightedVertex*)wg_adj(graph, target, &len);
        for (int i = 0; i < len; i++) {
            if (!visited[vertices[i].vertex]) {
                PQEdge* edge = (PQEdge*)malloc(sizeof(PQEdge));
                edge->v = target;
                edge->w = vertices[i].vertex;
                edge->weight = vertices[i].weight;
                pq_push(pq, edge);
            }
        }
    }

    pq_destroy(pq);
    free(visited);

    if (mstCount != graph->V - 1) {
        free(mst);
        *length = -1;
        return NULL;
    }

    *length = mstCount;
    return mst;
}