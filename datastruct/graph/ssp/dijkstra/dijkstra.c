#include "dijkstra.h"

void dijkstra_print(int* distTo, int* from, int end, char* result) {
  result[0] = '\0';  
  char temp[50];  
  int curr = end;
  while (curr != -1) {
      snprintf(temp, sizeof(temp), "%d(%d)", curr, distTo[curr]);
      strcat(result, temp);
      curr = from[curr];
      if (curr != -1) {
          strcat(result, " -> ");
      }
  }
}

void dijkstra(WeightedGraph* g, int s, char* result) {

  // 初始化 distTo 数组，用来记录起点到各个顶点的距离
  // distTo[起点] 为 0（自己到自己的距离为 0）
  // distTo[其他] 为 INT_MAX，方便后续比较，寻找距离更近的值
  int* distTo = (int*)malloc(g->V * sizeof(int));
  for (int i = 0; i < g->V; i++) {
    distTo[i] = INT_MAX;
  }
  distTo[s] = 0;

  // 初始化 from 路径，用来记录具体的路径信息，初始值为 -1 表示未到达
  int* from = (int*)malloc(g->V * sizeof(int));
  memset(from, -1, g->V * sizeof(int));

  // 维护 visited 数组，用来记录顶点访问状态
  // 初始状态下，所有值都赋值为 0
  int* visited = (int*)calloc(g->V, sizeof(int));

  while (true) {

    // 记录找到的最短距离以及相应的顶点信息，每一轮都要重置，从而保证可以正确找到最短路径及对应的顶点
    // minDist 用来在循环内更新，保证循环有效，能够找到最短路径顶点
    // minV 用来确定找到了最短路径的顶点信息，方便后面更新 visited 信息
    int minDist = INT_MAX;
    int minV = -1;

    // 遍历所有顶点，找到未访问的顶点里，路径最短的那个顶点
    // 未访问的顶点中，已经由某个其他顶点更新过路径的顶点，并且其已标记的距离是最短的，那一定就是最短路径
    // 因为已经被访问的顶点的最短路径都已经确认了，剩下还没有被访问的，也一定是经由其他被访问顶点过去的
    // 这种情况下的最短距离一定是确定的最短距离
    // 已访问：北京（0）、天津（100km）、保定（180km）
    // 未访问：石家庄（保定到石家庄 180km）、沧州（保定到沧州 150km）
    // 以上面的例子为例，北京到天津和保定的距离是确定的，这种情况下未访问顶点里的沧州就一定是最短路径
    // 因为这个地方是保定能到的最近的地方，随便去个其他地方再绕回来这里，都一定比这个距离更远
    // 每次选择当前"已知"最短距离的未访问顶点，这个顶点的最短路径一定已经确定，因为任何通过其他未访问顶点的路径都不可能更短
    // 贪心思想：每次都确定一个"一定不会错"的选择（当前最近的城市），然后通过这个选择去改善其他选择
    for (int v = 0; v < g->V; v++) {
      if (!visited[v] && distTo[v] < minDist) {
        minDist = distTo[v];
        minV = v;
      }
    }

    // 如果遍历完所有顶点，没有找到满足条件的顶点，则说明所有顶点都处理完了，结束循环
    if (minV == -1) break;

    // 更新 visited 数组，标记 minV 顶点，表示确定了到该顶点的最短路径
    // 当前顶点是还没确定距离的顶点里最短距离的顶点，前面的顶点都已经确定了最短路径，不可能再有其他顶点比当前这个更短
    visited[minV] = 1;

    // 从当前已经的最短路径的顶点出发，更新所有与该顶点相连的顶点的路径信息
    // 根据新找到的这条最短路，去更新【可以到达的其他顶点】，尝试优化之前的结论
    int length = 0;
    WeightedVertex* vertices = wg_adj(g, minV, &length);
    for (int i = 0; i < length; i++) {
      int vertex = vertices[i].vertex;
      int weight = vertices[i].weight;
      // 如果当前顶点还没有确定最短路径，并且新的路径比之前确定的路径更短，就更新一下当前顶点的距离信息
      // !visited[vertex] 的判断实际上没用，因为 visited 标记的顶点都是最短路径，后面的判断也不会生效
      // 这里只是为了语意清晰，明确表达只关心未访问顶点的距离
      if (!visited[vertex] && distTo[minV] + weight < distTo[vertex]) {
        distTo[vertex] = distTo[minV] + weight;
        // 在更新距离的同时更新来时路径
        from[vertex] = minV;
      }
    }
    free(vertices);
  }
  dijkstra_print(distTo, from, g->V - 1, result);
  free(distTo);
  free(from);
}

// 从终点往回找，直到起点
void print_path(int* from, int s, int t) {
    if (s == t) {
        printf("%d", s);
        return;
    }
    print_path(from, s, from[t]);
    printf(" -> %d", t);
}
