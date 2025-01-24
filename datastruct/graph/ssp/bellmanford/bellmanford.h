#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "../../adj/weighted_graph.h"
#include "string.h"
#include <limits.h>

void bellmanford(WeightedGraph* g, int s, char* result);

#endif