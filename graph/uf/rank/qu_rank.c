#include "qu_rank.h"

RankQuickUnion* qu_create(int n) {
  RankQuickUnion *qu = (RankQuickUnion*)malloc(sizeof(RankQuickUnion));
  qu->count = 0;
  qu->parent = (int*)malloc(sizeof(int) * n);
  qu->rank = (int*)malloc(sizeof(int) * n);

  // 初始化的时候，每个节点都指向自己，rank 都是 0
  for (int i = 0; i < n; i++) {
    qu->parent[i] = i;
    qu->rank[i] = 0;
  }
  return qu;
}

void qu_destroy(QuickUnion *qu) {
  free(qu->parent);
  free(qu->rank);
  free(qu);
}

int qu_find(QuickUnion *qu, int p) {
  // 找到根节点
  int root = p;
  while (root != qu->parent[root]) {
    root = qu->parent[root];
  }

  // 压缩路径：如果一个节点有超过一个父节点，则跳过第一个父节点，直接去链接第二个
  // 将所有节点都直接链接到根节点
  while (p != root) {
    // 先取出当前节点的父节点备用
    int next = qu->parent[p];
    // 将当前节点的父节点直接指向 root
    qu->parent[p] = root;
    // 更新 p 为当前节点的直系父节点
    // 如果已经指向 root 了，此时 next 就是 root，下一步可以跳出循环
    // 如果中间有多余的父节点，上面一步把当前节点直接指向了父节点，然后把 p 更新为原本的上层节点，然后继续循环处理上层节点
    p = next;
  }

  return p;
}

int qu_find_recursive(QuickUnion *qu, int p) {
  // p == parent[p] 就说明自己指向自己，已经是根节点了
  if (p != qu->parent[p]) {
    // 不断递归查找根节点，将当前节点直接指向根节点
    // p 与 parent[p] 大部分时间下都是不同的，即使已经被压缩的节点也是一样
    // 只不过，被压缩过的节点只需要一次就可以跳出递归，开销可以忽略不计
    // 我们无法预先知道一个节点是否已经被压缩，这个可以统一处理所有情况
    qu->parent[p] = qu_find_recursive(qu, qu->parent[p]);
  }
  return qu->parent[p];
}

void qu_union(QuickUnion *qu, int p, int q) {
  int pRoot = qu_find(qu, p);
  int qRoot = qu_find(qu, q);
  if (pRoot != qRoot) {
    // 比较 rank，将 rank 小的树连接到 rank 大的树上
    if (qu->rank[pRoot] < qu->rank[qRoot]) {
      qu->parent[pRoot] = qRoot;
    } else if (qu->rank[pRoot] > qu->rank[qRoot]) {
      qu->parent[qRoot] = pRoot;
    } else {
      // 相等的时候，随便选一个作为根，并维护相对应的 rank 信息
      qu->rank[qRoot] = pRoot;
      qu->rank[qRoot]++;
    }
  }
}

bool qu_connected(QuickUnion *qu, int p, int q) {
  int pRoot = qu_find(qu, p);
  int qRoot = qu_find(qu, q);
  return pRoot == qRoot;
}
