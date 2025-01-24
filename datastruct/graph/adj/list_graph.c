#include "list_graph.h"

// 由传入的新顶点构建一个新的链表节点，存储当前顶点信息以及下一个节点
VertexNode* createVertexNode(int vertex) {
  VertexNode* newNode = (VertexNode*)malloc(sizeof(VertexNode));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
}

void resetVisitedStatus(ListGraph* graph) {
  for (int i = 0; i < graph->V; i++){
    graph->visited[i] = -1;
    graph->preceder[i] = -1;
    graph->colors[i] = -1;
    graph->distance[i] = -1;
  }
}

ListGraph* lg_create(int capacity) {
  ListGraph* graph = (ListGraph*)malloc(sizeof(ListGraph));
  
  // 初始化基本信息，空图没有顶点也没有边
  graph->V = 0;
  graph->E = 0;
  graph->capacity = capacity;

  // 给每个位置都初始化一个数组
  // 数组中存储的是【与当前顶点相连】的所有其他顶点，以链表的形式存储，所以这里只需要存一个链表头节点即可
  graph->adj = (VertexNode**)malloc(capacity * sizeof(VertexNode*));
  for (int i = 0; i < capacity; i++) {
    // 开始的时候给每个数组都赋值为 NULL，表示当前没有连接任何顶点
    graph->adj[i] = NULL;
  }

  // 为每个顶点都在 visited 数组中初始化遍历状态
  graph->visited = (int*)malloc(capacity * sizeof(int));

  // 初始化前驱顶点的数组
  graph->preceder = (int*)malloc(capacity * sizeof(int));

  // 二分图检测时染色使用
  graph->colors = (int*)malloc(capacity * sizeof(int));

  // 记录顶点之间的距离
  graph->distance = (int*)malloc(capacity * sizeof(int));

  return graph;
}

void lg_destroy(ListGraph* graph) {
  for(int i = 0; i < graph->V; i++) {
    // 每个顶点都对应着一个链表，从链表头开始遍历回收
    VertexNode* current = graph->adj[i];
    while (current != NULL) {
      VertexNode* temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(graph->adj);
  free(graph->visited);
  free(graph->preceder);
  free(graph->colors);
  free(graph->distance);
  free(graph);
}

// 按顺序向图中添加一个顶点，不能超过最开始初始化的图大小
int lg_addVertex(ListGraph* graph) {
  assert(graph->V < graph->capacity);
  return graph->V++;
}

void lg_addEdge(ListGraph* graph, int a, int b) {
  assert((a >= 0 && a < graph->V) && (b >= 0 && b < graph->V));

  VertexNode* newNode = NULL;

  // 添加边 a -> b
  newNode = createVertexNode(b);     // 新建一个存储了 b 顶点信息的链表节点
  newNode->next = graph->adj[a];  // 把这个新节点插入到 graph->adj[a] 这个链表的链表头
  graph->adj[a] = newNode;        // 更新 graph->adj[a] 链表为最新的链表头

  // 添加边 b -> a
  newNode = createVertexNode(a);     // 新建一个存储了 a 顶点信息的链表节点 
  newNode->next = graph->adj[b];  // 让这个新链表指向 graph->adj[b] 的链表，成为该链表的头节点
  graph->adj[b] = newNode;        // 更新 graph->adj[b] 存储的链表为最新的链表头

  graph->E++;
}

// 获取与顶点 v 相连接的所有顶点信息
AdjList lg_adj(ListGraph* graph, int v){
  assert(v >= 0 && v < graph->V);

  AdjList result = { NULL, 0 };

  int* temp = (int*)malloc(graph->V * sizeof(int));
  int index = 0;

  // 从当前节点存储的第一个节点开始遍历
  VertexNode* current = graph->adj[v];
  while (current != NULL) {
    // 因为链表只会存储真正连接的顶点，所以不需要判断，直接赋值即可
    temp[index] = current->vertex;
    index++;
    current = current->next;
  }

  // 调整最终的相邻节点数据
  result.neighbours = (int*)realloc(temp, index * sizeof(int));
  result.count = index;

  return result;
}

// 从某个顶点开始，对整张图进行递归遍历
// 先访问当前节点，然后通过 adj() 得到当前节点的所有相连接的节点，之后再一一调用 dfs 访问该节点
void dfs(ListGraph* graph, int vertex, int ccId, int preceder) {
  // 访问当前节点
  printf("%d ", vertex);
  graph->visited[vertex] = ccId;
  // 记录当前顶点是从哪个顶点过来的
  graph->preceder[vertex] = preceder;
  // 通过 adj() 得到当前顶点的所有相连顶点
  AdjList adjList = lg_adj(graph, vertex); 
  for (int i = 0; i < adjList.count; i++) {
    // 遍历访问每个相连顶点
    int neighbour = adjList.neighbours[i];
    // 如果该顶点还未被访问过，就继续递归向下执行
    if (graph->visited[neighbour] == -1) {
      // neighbour 是 vertex 的相邻节点，也就是从 vertex 遍历到的 neighbour 顶点
      dfs(graph, neighbour, ccId, vertex);
    }
  }
}

// 对图进行深度优先遍历
void lg_dfs(ListGraph* graph) {
  resetVisitedStatus(graph); 
  printf("\nAdjacency List DFS: \n");
  // 通过增加 ccCount 变量，并在循环中进行自增，来记录整张图中不同的联通分量
  int ccCount = 0;
  // 遍历所有顶点，尝试 dfs 调用，因为图中有可能有多个联通分量
  // 在开始前先判断 visited 标记，以免重复遍历
  for (int i = 0; i < graph->V; i++) {
    if (graph->visited[i] == -1) {
      printf("cc%d: ", ccCount);
      dfs(graph, i, ccCount++, i);
      printf("\n");
    }
  }
  printf("\n");
}

// 对图进行广度优先遍历
void bfs(ListGraph* graph, int vertex, int ccId) {
  // 与二叉树的广度优先遍历类似，使用队列来实现
  CircularQueue* queue = cq_create(graph->V);
  // 从顶点 0 开始遍历
  cq_enqueue(queue, vertex);
  graph->visited[vertex] = ccId;
  // 记录距离信息
  graph->distance[vertex] = 0;
  // 记录当前顶点遍历的路径
  graph->preceder[vertex] = vertex;

  while (!cq_isEmpty(queue)) {
    // 从队列中取出顶点
    int vertex = cq_dequeue(queue);
    // 访问当前顶点
    printf("%d(%d) ", vertex, graph->distance[vertex]);
    // 通过 adj() 得到当前顶点的所有相连顶点
    AdjList adjList = lg_adj(graph, vertex); 
    for (int i = 0; i < adjList.count; i++) {
      int neighbour = adjList.neighbours[i];
      // 如果该顶点还未被访问过，就继续递归向下执行
      if (graph->visited[neighbour] == -1) {
        // 如果当前顶点还没有被访问过，就将当前顶点入队，然后标记为已访问
        cq_enqueue(queue, neighbour);
        graph->visited[neighbour] = ccId;
        // 记录路径
        graph->preceder[neighbour] = vertex;
        // neighbour 顶点到根顶点的距离 = 当前顶点到根顶点的距离 + 1
        graph->distance[neighbour] = graph->distance[vertex] + 1;
      }
    } 
  }
  cq_destroy(queue);
}

void lg_bfs(ListGraph* graph) {
  resetVisitedStatus(graph);
  printf("\nAdjacency List BFS: \n");
  // 通过增加 ccCount 变量，并在循环中进行自增，来记录整张图中不同的联通分量
  int ccCount = 0;
  for (int i = 0; i < graph->V; i++) {
    if (graph->visited[i] == -1) {
      printf("cc%d: ", ccCount);
      bfs(graph, i, ccCount++);
      printf("\n");
    }
  }
}

int* lg_path_bfs(ListGraph* graph, int a, int b, int* len) {
  resetVisitedStatus(graph);
  bfs(graph, a, 0);
  if (lg_isConnected(graph, a, b)) {

    // 先把总路径长度计算出来
    int count = 1; // 从 1 开始是因为需要把起终点都算上
    int current = b; // 从终点 b 开始向回查找
    while (current != a) {
      count++;
      current = graph->preceder[current];
    }

    int *path = (int*)malloc(count * sizeof(int));

    // 正向存储路径信息
    current = b;
    int index = count - 1;
    path[index] = current;
    while(current != a) {
      index--;
      current = graph->preceder[current];
      path[index] = current;
    }

    *len = count;
    return path;
  }
  return NULL; 
}

static bool hasCycle_bfs(ListGraph* graph, int vertex) {
  CircularQueue* queue = cq_create(graph->V);
  // 标记当前顶点已访问
  graph->visited[vertex] = 1;
  // 记录当前顶点是从谁遍历过来的
  graph->preceder[vertex] = vertex;

  // 入队
  cq_enqueue(queue, vertex);

  while (!cq_isEmpty(queue)) {
    int v = cq_dequeue(queue);
    AdjList adj = lg_adj(graph, v);
    for (int i = 0; i < adj.count; i++) {
      int neighbour = adj.neighbours[i];
      if (graph->visited[neighbour] == -1) {
        // 如果没有访问过该顶点，入队
        cq_enqueue(queue, neighbour);
        graph->visited[neighbour] = 1;
        graph->preceder[neighbour] = v;
      }
      // 如果已经访问过了，就要看一下这个是怎么来的
      else if (neighbour != graph->preceder[v]) {
        cq_destroy(queue);
        return true;
      }
    }
  }
  cq_destroy(queue);
  return false;
}

bool lg_hasCycle_bfs(ListGraph* graph) {
  resetVisitedStatus(graph);
  for (int i = 0; i < graph->V; i++) {
    if (graph->visited[i] == -1) {
      if (hasCycle_bfs(graph, i)) {
        return true;
      }
    }
  }
  return false;
}

bool isBipartite_bfs(ListGraph* graph, int vertex) {
  CircularQueue* queue = cq_create(graph->V);

  // 给当前节点染色后入队
  // BFS 下，不再使用传入的 color 参数，而是在循环的过程中直接去取值
  graph->colors[vertex] = 0;
  cq_enqueue(queue, vertex);

  while(!cq_isEmpty(queue)) {
    int v = cq_dequeue(queue);
    AdjList list = lg_adj(graph, v);
    for (int i = 0; i < list.count; i++) {
      int neighbour = list.neighbours[i];
      if (graph->colors[neighbour] == -1) {
        // 如果还没有染过色，就递归向下，注意相邻节点的颜色不一样
        graph->colors[neighbour] = 1 - graph->colors[v];
        cq_enqueue(queue, neighbour);
      }
      // 如果已经染过色了，就判断颜色是否冲突
      else if (graph->colors[neighbour] == graph->colors[v]) {
        cq_destroy(queue);
        return false;
      }
    }
  }

  cq_destroy(queue);
  return true;
}

bool lg_isBipartite_bfs(ListGraph* graph) {
  resetVisitedStatus(graph);
  for (int i = 0; i < graph->V; i++) {
    if (graph->colors[i] == -1) {
      if (!isBipartite_bfs(graph, i)) {
        // 只要有一个联通分量不满足二分图的条件，就认为不是
        return false;
      }
    }
  }
  return true;
}

// ----------------------- 检测联通分量 -----------------------

// 通过在 visited 数组中存储联通分量的 id，从而保证同一联通分量中的顶点值都相同
// 从而保证方便地判断两个顶点之间是否是连接的
// 这里的 visited 数组，实际上就是并查集的应用，这里就是 quickFind 的实现
bool lg_isConnected(ListGraph* graph, int a, int b) {
  return graph->visited[a] == graph->visited[b];
}

// ----------------------- 检测联通分量 -----------------------

// ----------------------- 单源路径检测 -----------------------
int* lg_path(ListGraph* graph, int a, int b, int* len) {
  resetVisitedStatus(graph);

  // 从目标起点开始遍历整个图，以免因为插入顺序导致查询的时候找不到正确的路径
  // 比如按照 (2,1) (2,3) (1,0) 这个顺序建图
  // 如果想找到 0->3 的路径，从 0 开始遍历是找不到的，比如从 2 开始遍历才可以
  dfs(graph, a, 0, a);

  if (lg_isConnected(graph, a, b)) {

    // 先把总路径长度计算出来
    int count = 1; // 从 1 开始是因为需要把起终点都算上
    int current = b; // 从终点 b 开始向回查找
    while (current != a) {
      count++;
      current = graph->preceder[current];
    }

    int *path = (int*)malloc(count * sizeof(int));

    // 正向存储路径信息
    current = b;
    int index = count - 1;
    path[index] = current;
    while(current != a) {
      index--;
      current = graph->preceder[current];
      path[index] = current;
    }

    *len = count;
    return path;
  }
  return NULL;
}
// ----------------------- 单源路径 -----------------------

// ----------------------- 环 -----------------------
static bool hasCycle(ListGraph* graph, int vertex, int parent) {
  // 标记当前顶点被访问过了
  graph->visited[vertex] = 1;

  // 遍历所有相邻顶点
  AdjList adj = lg_adj(graph, vertex);
  for (int i = 0; i < adj.count; i++) {
    int neighbour = adj.neighbours[i];
    // 如果当前 neighbour 顶点还没有被访问过，就继续向下，同时把 vertex 作为其 parent 一起维护好
    if (graph->visited[neighbour] == -1) {
      hasCycle(graph, neighbour, vertex);
    } 
    // 如果当前 neighbour 顶点已经被访问过了，并且不是父顶点，就说明找到了环
    // 假设存在图 0 1 2，其中 0 - 1，0 - 2，1 - 2
    // 1. dfs(0, 0)，0 与 1 相连，递归执行 dfs(1, 0)
    // 2. dfs(1, 0), 1 的相邻顶点有 0 和 2 两个，检查 0 的时候发现 0 已经访问过了，
    //    此时 neighbour 是 0，但是 parent 也是 0，不能判断为环；
    //    再检查 2，没有访问过，继续执行 dfs(2, 1)
    // 3. dfs(2, 1), 2 的相邻顶点有 0 和 1 两个，检查 0 的时候发现 0 已经访问过了，
    //    此时 neighbour 是 0，但是 parent 为 1，说明有环，结束匹配；
    // 总结来看，整个流程是：
    // 1. 从 0 开始遍历，
    // 2. 遍历到 1 时，1 有 0 和 2 两个相连顶点，
        // 2.1 遍历到 0 时，0 忽略不计，因为这两个顶点直接相连；
        // 2.2 遍历到 2 时，2 有 0 和 1 两个相连顶点，
            // 2.2.1 遍历到 0 时，0 已经访问过，并且本次遍历是从 1 过来的，说明有环
            // 从 v 开始遍历，最终再次访问到了 v，且访问到 v 的时候不是从 v 过来的，就可以说明有环
    else if (neighbour != parent) {
      return true;
    }
  }
  return false;
}

bool lg_hasCycle(ListGraph* graph) {
  resetVisitedStatus(graph);
  // 遍历所有顶点，确保覆盖到所有联通分量
  for (int i = 0; i < graph->V; i++) {
    // 如果当前顶点还没有被访问过，继续向下递归执行
    if (graph->visited[i] == -1) {
      if (hasCycle(graph, i, i)) {
        // 如果从当前顶点出发，最后找到了环，就直接返回
        return true;
      }
    } 
  }
  return false;
}
// ----------------------- 环 -----------------------

// ----------------------- 二分图 -----------------------
bool isBipartite(ListGraph* graph, int vertex, int color) {
  // 给当前顶点染色
  graph->colors[vertex] = color;
  // 遍历所有连接的点，还没有访问过的都染成另外的颜色
  AdjList list = lg_adj(graph, vertex);
  for (int i = 0; i < list.count; i++) {
    int neighbour = list.neighbours[i];
    if (graph->colors[neighbour] == -1) {
      // 如果当前访问到的顶点还没有被访问过，即没有染过色，则继续递归向下
      // 将所有相邻的顶点都染成其他颜色
      if(!isBipartite(graph, neighbour, 1 - color)){
        // 如果递归返回 false，说明有子图不是二分图，直接返回 false 即可
        return false;
      }
    } 
    // 如果已经访问过了，就要检查一下是不是相同的颜色
    else if (graph->colors[neighbour] == color) {
      return false;
    }
  }
  return true;
}

bool lg_isBipartite(ListGraph* graph) {
  resetVisitedStatus(graph);
  for (int i = 0; i < graph->V; i++) {
    if (graph->colors[i] == -1) {
      // 只要有一个连通分量不是二分图，整个图就不是
      if (!isBipartite(graph, i, 0)) {
        return false;
      }
    }
  }
  return true;
}
// ----------------------- 二分图 -----------------------

// void lg_print(ListGraph* graph) {
  // printf("Adjacency List:\n");
  // for (int i = 0; i < graph->V; i++) {
  //   printf("%d: ", i);
  //   VertexNode* current = graph->adj[i];
  //   while (current != NULL) {
  //     printf("%d -> ", current->vertex);
  //     current = current->next;
  //   }
  //   printf("NULL\n");
  // }
// }

