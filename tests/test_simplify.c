#include "digraph.h"
#include <stdio.h>

#define NODE_COUNT 8

int main() {
  unsigned char graph[DIGRAPH_ADJ_MATRIX_SIZE(NODE_COUNT)] = {0};
  DiGraph_addEdge(graph, NODE_COUNT, 0, 1);
  DiGraph_addEdge(graph, NODE_COUNT, 1, 2);
  DiGraph_addEdge(graph, NODE_COUNT, 0, 2); // Redundant edge
  DiGraph_simplify(graph, NODE_COUNT);

  if (DiGraph_hasEdge(graph, NODE_COUNT, 0, 2)) {
    printf("[FAILED] test_simplify: Redundant edge 0->2 should be removed\n");
    return 1;
  }

  printf("[PASSED] test_simplify\n");
  return 0;
}
