#ifndef MST_PRIM_H
#define MST_PRIM_H

#include "weighted_graph.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int v;
    int w;
    int weight;
} PEdge;

PEdge* prim(WeightedGraph* graph, int* length);

#endif