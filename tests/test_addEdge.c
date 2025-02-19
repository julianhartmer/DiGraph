#include "digraph.h"
#include <stdio.h>

#define NODE_COUNT 8

int main() {
  unsigned char graph[DIGRAPH_ADJ_MATRIX_SIZE(NODE_COUNT)] = {0};
  DiGraph_addEdge(graph, NODE_COUNT, 0, 1);

  if (!DiGraph_hasEdge(graph, NODE_COUNT, 0, 1)) {
    printf("[FAILED] test_addEdge: Edge 0->1 should exist\n");
    return 1;
  }

  printf("[PASSED] test_addEdge\n");
  return 0;
}
