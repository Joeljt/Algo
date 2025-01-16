## Kruskal

Kruskal 算法的思想很简单，整个算法实际上就是无脑应用切分定理的过程。

切分定理规定，在一个切分中，最短的横切边一定属于最小生成树。

基于这个前提，Kruskal 算法分为几个步骤实现：

1. 收集图中所有的边，并对其进行升序排序；
2. 每次取出来最短的边并确定其是否是横切边，即两端顶点不属于同一切分；
3. 找到最短的横切边，将其加入最小生成树；
4. 循环 2 和 3，直到遍历完所有边或者最小生成树已经收集到了 V - 1 条边；

### 代码实现

收集所有边并进行排序：

```c
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
// 对所有边进行排序
qsort(allEdges, edgeCount, sizeof(KEdge), compareEdges);
```

取出当前最短的那个横切边：

```c

```


