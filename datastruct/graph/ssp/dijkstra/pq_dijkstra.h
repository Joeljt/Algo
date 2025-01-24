#ifndef PQ_DIJKSTRA_H
#define PQ_DIJKSTRA_H

#include "../../adj/weighted_graph.h"
#include "../../../queue/priority/priority_queue.h"
#include "string.h"
#include <limits.h>

void pq_dijkstra(WeightedGraph* g, int s, char* result);

#endif