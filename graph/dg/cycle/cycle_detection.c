#include "cycle_detection.h"

static bool hasCycle_dfs(DirectedGraph* g, int v) {
  // 标记当前顶点正在被访问
  g->visitState[v] = VISITING; // 1. 进入顶点时标记为 VISITING
  // 遍历当前顶点的所有相邻顶点
  int len = 0;
  DEdge* edges = dg_adj(g, v, &len);
  for (int i = 0; i < len; i++) {
    int neighbour = edges[i].vertex;
    // 如果发现相邻顶点正在被访问，说明有环
    if (g->visitState[neighbour] == VISITING) { // 2. 如果遇到 VISITING 状态，说明找到环
      free(edges);
      return true;
    } else if (g->visitState[neighbour] == UNVISITED) {
      // 如果相邻顶点未被访问，则递归访问相邻顶点，并且回溯判断是否存在环
      if (hasCycle_dfs(g, neighbour)) { // 3. 继续深入访问相邻顶点
        free(edges);
        return true;
      }
    }
    // 如果相邻顶点已访问，则跳过该节点，继续遍历下一个
  }
  // 如果没有找到环，就标记当前顶点已访问
  // 注意这个访问状态是递归回溯的，当一个顶点的所有邻接点都访问完成后，该顶点就会从 VISITING 变为 VISITED
  g->visitState[v] = VISITED;  // 4. 关键点：递归回溯时标记为 VISITED
  free(edges);
  return false;
}

bool dg_hasCycle(DirectedGraph* g) {
  // 初始化所有顶点的访问状态为未访问
  for (int i = 0; i < g->V; i++) {
    g->visitState[i] = UNVISITED;
  }
  // 遍历所有顶点，如果有未访问的顶点，就向下进行 dfs 搜索
  for (int i = 0; i < g->V; i++) {
    if (g->visitState[i] == UNVISITED) {
      if (hasCycle_dfs(g, i)) return true;
    }
  }
  return false;
}

static bool hasCycle2_dfs(DirectedGraph* g, int v) {
  // 标记当前顶点为已访问，并记录到路径中
  g->visited[v] = 1; 
  g->onPath[v] = 1; // 1. 进入时标记，设置当前状态

  // 遍历当前顶点的所有相邻顶点
  int len = 0;
  DEdge* edges = dg_adj(g, v, &len);
  for (int i = 0; i < len; i++) {
    int neighbour = edges[i].vertex; 
    // 如果当前顶点没有访问过，直接继续 dfs
    if (!g->visited[neighbour]) {
      if (hasCycle2_dfs(g, neighbour)) { // 2. 递归处理：处理子问题
        free(edges);
        return true;
      }
    }
    // 如果当前顶点之前就访问过，检查是不是在路径上，如果是就说明有环
    else if (g->onPath[neighbour]){ 
      free(edges);
      return true;
    }
  }
  // 完成了对某个顶点的所有邻接点的访问后，就要从这个顶点返回了
  // 这时候这个顶点就不再是当前正在检查的路径的一部分的，需要将其从路径标记中移除
  // 实际上也是在完成递归，向上回溯的时候重置标记状态的操作
  g->onPath[v] = 0; // 3. 离开时清除：恢复之前的状态

  free(edges);
  return false;
}

bool dg_hasCycle2(DirectedGraph* g) {
  for (int i = 0; i < g->V; i++) {
    g->visited[i] = 0;
    g->onPath[i] = 0;
  }

  for (int i = 0; i < g->V; i++) {
    if (!g->visited[i]) {
      if (hasCycle2_dfs(g, i)) {
        return true;
      }
    }
  }

  return false;
}