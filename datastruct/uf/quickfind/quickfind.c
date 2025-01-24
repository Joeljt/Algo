#include "quickfind.h"

QuickFind* qf_create(int n) {
  QuickFind *qf = (QuickFind *)malloc(sizeof(QuickFind));
  qf->id = (int *)malloc(n * sizeof(int));
  qf->count = n;

  // 初始化的时候，每个元素都是独立的集合，彼此之间没有连接
  for (int i = 0; i < n; i++) {
    qf->id[i] = i;
  }
  return qf;
}

void qf_destroy(QuickFind *qf) {
  free(qf->id);
  free(qf);
}

// 之所以叫 quick find，是因为 find 操作非常快，可以在 O(1) 内返回
// find 操作就是简单地返回元素所属的集合编号，即在数组中对应的值
int qf_find(QuickFind *qf, int p) {
  return qf->id[p];
}

bool qf_connected(QuickFind *qf, int p, int q) {
  return qf_find(qf, p) == qf_find(qf, q);
}

void qf_union(QuickFind *qf, int p, int q) {
  int pRoot = qf_find(qf, p);
  int qRoot = qf_find(qf, q);
  if (pRoot != qRoot) {
    // 将集合中所有与目标元素不在同一集合的元素，都放到同一个元素（更新存储的集合 id 的值）
    for (int i = 0; i < qf->count; i++) {
      // 将所有的 pRoot 集合都更新为 qRoot，这样就相当于完成了 union 操作
      if (qf->id[i] == pRoot) {
        qf->id[i] = qRoot;
      }
    }
  }
}

