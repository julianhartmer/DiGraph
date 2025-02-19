#include "digraph.h"
#include <stdio.h>

#define NODE_COUNT 8

int main() {
  unsigned char graph[DIGRAPH_ADJ_MATRIX_SIZE(NODE_COUNT)] = {0};
  unsigned char buf[DIGRAPH_ADJ_MATRIX_SIZE(NODE_COUNT) +
                    2 * DIGRAPH_NODE_ARRAY_SIZE(NODE_COUNT)];

  DiGraph_addEdge(graph, NODE_COUNT, 0, 1);
  DiGraph_addEdge(graph, NODE_COUNT, 1, 2);
  if (!DiGraph_isAcyclic(graph, NODE_COUNT, buf)) {
    printf("[FAILED] test_isAcyclic: Graph should be acyclic\n");
    return 1;
  }

  DiGraph_addEdge(graph, NODE_COUNT, 2, 0); // Creating a cycle
  if (DiGraph_isAcyclic(graph, NODE_COUNT, buf)) {
    printf("[FAILED] test_isAcyclic: Graph should be cyclic\n");
    return 1;
  }

  printf("[PASSED] test_isAcyclic\n");
  return 0;
}