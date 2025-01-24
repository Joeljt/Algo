#ifndef TOPO_SORT_H
#define TOPO_SORT_H

#include <stdbool.h>

#include "directed_graph.h"
#include "cycle/cycle_detection.h"
#include "../../queue/circular/circular_queue.h"

int* topo_sort(DirectedGraph* g, int* length);
int* topo_sort_dfs(DirectedGraph* g, int* length);

#endif