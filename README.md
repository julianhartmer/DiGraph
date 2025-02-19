# DiGraph Library

## Overview
DiGraph is a lightweight C library for handling directed graphs efficiently using a bitfield-based adjacency matrix. The library provides functions for adding and removing edges, checking for cyclic dependencies, and simplifying graphs by removing redundant edges.

## Features
- **Bitfield adjacency matrix representation** for space efficiency.
- **Basic graph operations**: Add and remove edges.
- **Cycle detection**: Check if a graph is acyclic.
- **Graph simplification**: Remove redundant edges.

## Usage

### Compiling
Ensure you include `digraph.h` and link your project with the corresponding implementation files.

### Example
```c
#include <stdio.h>
#include "digraph.h"

#define NODE_COUNT 8

int main() {
    unsigned char graph[DIGRAPH_ADJ_MATRIX_SIZE(NODE_COUNT)] = {0};
    DiGraph_addEdge(graph, NODE_COUNT, 0, 1);
    printf("Edge from 0 to 1 exists: %s\n", DiGraph_hasEdge(graph, NODE_COUNT, 0, 1) ? "Yes" : "No");
    return 0;
}
```

## Documentation
For detailed function descriptions and API usage, refer to the `digraph.h` header file.

## License
This library is licensed under the MIT License, allowing usage in any product without liability. 

**Copyright (c) Julian Hartmer**  
Contact: j.hartmer@googlemail.com
