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

// 通过在 visited 数组中存储联通分量的 id，从而保证同一联通分量中的顶点值都相同
// 从而保证方便地判断两个顶点之间是否是连接的
// 这里的 visited 数组，实际上就是并查集的应用，这里就是 quickFind 的实现
bool lg_isConnected(ListGraph* graph, int a, int b) {
  return graph->visited[a] == graph->visited[b];
}

// 单源路径
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

void lg_print(ListGraph* graph) {
  printf("Adjacency List:\n");
  for (int i = 0; i < graph->V; i++) {
    printf("%d: ", i);
    VertexNode* current = graph->adj[i];
    while (current != NULL) {
      printf("%d -> ", current->vertex);
      current = current->next;
    }
    printf("NULL\n");
  }
}

