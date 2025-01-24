#ifndef CYCLE_DETECTION_H
#define CYCLE_DETECTION_H

#include "../directed_graph.h"
#include <stdbool.h>

#define UNVISITED 0
#define VISITING 1
#define VISITED 2

bool dg_hasCycle(DirectedGraph* g);
bool dg_hasCycle2(DirectedGraph* g);

#endif