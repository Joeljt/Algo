#ifndef QUICKFIND_H
#define QUICKFIND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QuickFind {
  int *id; // 存储每个元素所属的集合编号
  int count; // 元素个数
} QuickFind;

QuickFind* qf_create(int n);
void qf_destroy(QuickFind *qf);

void qf_union(QuickFind *qf, int p, int q);
int qf_find(QuickFind *qf, int p);
bool qf_connected(QuickFind *qf, int p, int q);

void qf_print(QuickFind *qf);

#endif