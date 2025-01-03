#include "list_graph.h"

// 由传入的新顶点构建一个新的链表节点，存储当前顶点信息以及下一个节点
VertexNode* createVertexNode(int vertex) {
  VertexNode* newNode = (VertexNode*)malloc(sizeof(VertexNode));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
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

