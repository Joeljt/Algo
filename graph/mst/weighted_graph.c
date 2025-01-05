#include "weighted_graph.h"

// 创建新的顶点节点
static WeightedVertex* createVertexNode(int vertex, int weight) {
    WeightedVertex* newNode = (WeightedVertex*)malloc(sizeof(WeightedVertex));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

WeightedGraph* wg_create(int capacity) {
    WeightedGraph* graph = (WeightedGraph*)malloc(sizeof(WeightedGraph));
    graph->V = 0;
    graph->E = 0;
    graph->capacity = capacity;
    
    // 初始化邻接表数组
    graph->vertices = (WeightedVertex**)malloc(capacity * sizeof(WeightedVertex*));
    for(int i = 0; i < capacity; i++) {
        graph->vertices[i] = NULL;
    }
    
    return graph;
}

void wg_destroy(WeightedGraph* graph) {
    for(int i = 0; i < graph->V; i++) {
        WeightedVertex* current = graph->vertices[i];
        while(current != NULL) {
            WeightedVertex* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->vertices);
    free(graph);
}

int wg_addVertex(WeightedGraph* graph) {
    assert(graph->V < graph->capacity);
    return graph->V++;
}

void wg_addEdge(WeightedGraph* graph, int v, int w, int weight) {
    assert((v >= 0 && v < graph->V) && (w >= 0 && w < graph->V));
    
    // 添加边 v -> w
    WeightedVertex* newNode = createVertexNode(w, weight);
    newNode->next = graph->vertices[v];
    graph->vertices[v] = newNode;
    
    // 添加边 w -> v（无向图）
    newNode = createVertexNode(v, weight);
    newNode->next = graph->vertices[w];
    graph->vertices[w] = newNode;
    
    graph->E++;
}

int* wg_adj(WeightedGraph* graph, int v, int* length){
    assert(v >= 0 && v < graph->V);

    int* neighbours = (int*)malloc(graph->V * sizeof(int));
    int index = 0;

    // 从当前节点存储的第一个节点开始遍历
    WeightedVertex* current = graph->vertices[v];
    while (current != NULL) {
        // 因为链表只会存储真正连接的顶点，所以不需要判断，直接赋值即可
        neighbours[index] = current->vertex;
        index++;
        current = current->next;
    }

    // 调整最终的相邻节点数据
    neighbours = (int*)realloc(neighbours, index * sizeof(int));
    *length = index;

    return neighbours;
}

void wg_print(WeightedGraph* graph) {
    printf("\nWeighted Graph:\n");
    for(int v = 0; v < graph->V; v++) {
        printf("%d: ", v);
        WeightedVertex* current = graph->vertices[v];
        while(current != NULL) {
            printf("(%d,w:%d) -> ", current->vertex, current->weight);
            current = current->next;
        }
        printf("NULL\n");
    }
}