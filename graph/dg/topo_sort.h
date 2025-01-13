#ifndef TOPO_SORT_H
#define TOPO_SORT_H

#include "directed_graph.h"
#include "../../queue/circular/circular_queue.h"

int* topo_sort(DirectedGraph* g, int* length);

#endif