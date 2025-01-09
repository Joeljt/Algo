#include "bellmanford.h"

void bellmanford_print(int* distTo, int* from, int end, char* result) {
  result[0] = '\0';  
  char temp[50];  
  int curr = end;
  while (curr != -1) {
      snprintf(temp, "%d(%d)", curr, distTo[curr]);
      strcat(result, temp);
      curr = from[curr];
      if (curr != -1) {
          strcat(result, " -> ");
      }
  }
}

void bellmanford(WeightedGraph* g, int s, char* result) {
    
    int* distTo = (int*)malloc(g->V * sizeof(int));
    for (int i = 0; i < g->V; i++) {
        distTo[i] = INT_MAX;
    }
    distTo[s] = 0;

    // 初始化 from 路径，用来记录具体的路径信息，初始值为 -1 表示未到达
    int* from = (int*)malloc(g->V * sizeof(int));
    memset(from, -1, g->V * sizeof(int));

    // 遍历 V - 1 次
    for (int i = 0; i < g->V - 1; i++) {
        // 遍历所有顶点
        for (int v = 0; v < g->V; v++) {
            // 遍历当前顶点的所有邻接顶点
            int length = 0;
            WeightedVertex* wv = wg_adj(g, v, &length);
            for (int j = 0; j < length; j++) {
                int w = wv[j].vertex;
                int weight = wv[j].weight;
                // 如果当前顶点可达，且额外经过当前邻边到达顶点的距离比已知的更短，则进行更新
                // 即松弛操作
                // 注意在遍历相邻顶点的时候，是要给相邻顶点确定距离，所以比较和更新的都是相邻顶点的距离
                // 也就是 distTo[w], 而不是 distTo[v]
                if (distTo[v] != INT_MAX && distTo[v] + weight < distTo[w]) {
                    distTo[w] = distTo[v] + weight;
                    from[w] = v;
                }
            }
        }
    }

    // 在完成 V-1 次松弛操作后，所有的最短路径应该都已经被找到，
    // 再进行一次松弛操作如果这时还能找到更短的路径，就说明存在负权环。
    bool hasNegativeCycle = false;
    for (int v = 0; v < g->V; v++) {
        int length = 0;
        WeightedVertex* wv = wg_adj(g, v, &length);
        for (int j = 0; j < length; j++) {
            int w = wv[j].vertex;
            int weight = wv[j].weight;
            if (distTo[v] != INT_MAX && distTo[v] + weight < distTo[w]) {
                hasNegativeCycle = true;
                break;
            }
        }
        if (hasNegativeCycle) break;
    }

    if (hasNegativeCycle) {
        strcpy(result, "存在负权环");
    } else {
        bellmanford_print(distTo, from, g->V - 1, result);
    }

    free(distTo);
    free(from);
}