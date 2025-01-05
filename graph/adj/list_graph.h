#ifndef __LIST_GRAPH_H__
#define __LIST_GRAPH_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../queue/circular/circular_queue.h"

// 定义相邻节点的结构信息
typedef struct {
  int* neighbours;
  int count;
} AdjList;

// 定义邻接表节点
typedef struct VertexNode {
  int vertex;
  struct VertexNode* next;
} VertexNode;

// 定义图结构
typedef struct {
  int V;        // 当前顶点数
  int E;        // 当前边数
  int capacity; // 最大顶点容量
  int* visited; // 当前顶点是否被遍历过
  int* preceder; // 记录当前顶点是从哪个顶点遍历过来的
  int* colors;   // 二分图检测染色用
  int* distance; // 记录顶点之间的距离
  VertexNode** adj; // 存储顶点信息的数组，每个数组元素都是一个链表
} ListGraph;

ListGraph* lg_create(int capacity);
void lg_destroy(ListGraph* graph);

int lg_addVertex(ListGraph* graph);
void lg_addEdge(ListGraph* graph, int a, int b);
AdjList lg_adj(ListGraph* graph, int v);

void lg_dfs(ListGraph* graph);
void lg_bfs(ListGraph* graph);

bool lg_isConnected(ListGraph* graph, int a, int b);
int* lg_path(ListGraph* graph, int a, int b, int* len);
bool lg_hasCycle(ListGraph* graph);
bool lg_isBipartite(ListGraph* graph);

int* lg_path_bfs(ListGraph* graph, int a, int b, int* len);
bool lg_hasCycle_bfs(ListGraph* graph);
bool lg_isBipartite_bfs(ListGraph* graph);


// void lg_print(ListGraph* graph);

#endif