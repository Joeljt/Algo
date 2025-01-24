#include "quickunion.h"

QuickUnion* qu_create(int n) {
  QuickUnion *qu = (QuickUnion*)malloc(sizeof(QuickUnion));
  qu->count = 0;
  qu->parent = (int*)malloc(sizeof(int) * n);

  // 初始化的时候，每个节点都指向自己
  for (int i = 0; i < n; i++) {
    qu->parent[i] = i;
  }
  return qu;
}

void qu_destroy(QuickUnion *qu) {
  free(qu->parent);
  free(qu);
}

int qu_find(QuickUnion *qu, int p) {
  // 向上找当前节点的父节点，直到顶部，自己指向自己
  while (p != qu->parent[p]) {
    p = qu->parent[p];
  }
  return p;
}

void qu_union(QuickUnion *qu, int p, int q) {
  int pRoot = qu_find(qu, p);
  int qRoot = qu_find(qu, q);
  if (pRoot != qRoot) {
    // 将某个节点的父节点指向另一个节点，从而完成两个集合的连接
    // 注意这里需要是用 qRoot，也就是 q 的父节点
    qu->parent[pRoot] = qRoot;
  }
}

bool qu_connected(QuickUnion *qu, int p, int q) {
  int pRoot = qu_find(qu, p);
  int qRoot = qu_find(qu, q);
  return pRoot == qRoot;
}
