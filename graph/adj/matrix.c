#include "matrix.h"

static void check(AdjMatrix* g, int v, int w) {
    assert (v >= 0 && v < g->size);
    assert (w >= 0 && w < g->size);
}


AdjMatrix* am_create(int size){
    AdjMatrix* matrix = (AdjMatrix*)malloc(sizeof(AdjMatrix));
    matrix->size = size;

    // 给邻接矩阵分配内存
    // 申请 size 个数组空间，并赋值给 matrix 变量
    matrix->matrix = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) {
        // 给每个位置也都初始化 size 个元素
        matrix->matrix[i] = (int*)malloc(sizeof(int) * size);
        // 将所有元素初始化为 0
        for (int j = 0; j < size; j++)
            matrix->matrix[i][j] = 0;
        
        // 使用 calloc 可以达到一样的效果：申请内存并默认设置为 0
        // matrix->matrix[i] = (int*)calloc(sizeof(int) * size);
    }
    
    return matrix;
}

void am_destroy(AdjMatrix* matrix){

}

void am_add_edge(AdjMatrix* matrix, int src, int dest){
    check(matrix, src, dest);
    // 无向图，两个方向都需要标记连接
    matrix->matrix[src][dest] = 1;
    matrix->matrix[dest][src] = 1;
}


void am_remove_edge(AdjMatrix* matrix, int src, int dest){

}

bool am_has_edge(AdjMatrix* matrix, int src, int dest){

}

void am_print(AdjMatrix* matrix) {

}