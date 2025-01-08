#ifndef PQ_PRIM_H
#define PQ_PRIM_H

#include "../../adj/weighted_graph.h"
#include "../../../queue/priority/priority_queue.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int v;
    int w;
    int weight;
} PQEdge;

PQEdge* pq_prim(WeightedGraph* graph, int* length);


#endif