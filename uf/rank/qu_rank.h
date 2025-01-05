#ifndef QU_RANK_H
#define QU_RANK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 在 quickunion 的基础上，增加 rank 来记录树的深度
// 通过记录树的高度，在合并的时候可以尽可能保持树的平衡，避免退化为链表
typedef struct RankQuickUnion {
  int *parent; // 存放父节点索引
  int *rank; // 存放树的深度
  int count; // 元素个数
} RankQuickUnion;

RankQuickUnion* qu_rank_create(int n);
void qu_rank_destroy(RankQuickUnion *qu);

bool qu_rank_connected(RankQuickUnion *qu, int p, int q);
void qu_rank_union(RankQuickUnion *qu, int p, int q);
int qu_rank_find(RankQuickUnion *qu, int p);
int qu_rank_find_recursive(RankQuickUnion *qu, int p);

void qu_rank_print(RankQuickUnion *qu);

#endif
