#ifndef PRIM_H
#define PRIM_H

#include "../../adj/weighted_graph.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int v;
    int w;
    int weight;
} PEdge;

PEdge* prim(WeightedGraph* graph, int* length);

#endif