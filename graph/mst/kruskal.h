#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "weighted_graph.h"
#include "../../uf/rank/qu_rank.h"
#include <stdio.h>
typedef struct {
    int v;
    int w;
    int weight;
} KEdge;

KEdge* kruskal(WeightedGraph* graph, int* length);

#endif