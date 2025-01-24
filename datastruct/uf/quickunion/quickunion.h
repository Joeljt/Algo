#ifndef QU_H
#define QU_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QuickUnion {
  int *parent; // 存放父节点索引
  int count; // 元素个数
} QuickUnion;

QuickUnion* qu_create(int n);
void qu_destroy(QuickUnion *qu);

void qu_union(QuickUnion *qu, int p, int q);
int qu_find(QuickUnion *qu, int p);
bool qu_connected(QuickUnion *qu, int p, int q);

void qu_print(QuickUnion *qu);

#endif