/*
 * DiGraph Library
 *
 * A lightweight C library for handling directed graphs efficiently using a
 * bitfield-based adjacency matrix.
 *
 * Author: Julian Hartmer
 * Contact: j.hartmer@googlemail.com
 * License: MIT License
 *
 * MIT License
 *
 * Copyright (c) 2025 Julian Hartmer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DIGRAPH_H
#define DIGRAPH_H

#ifndef CEILING_DIV
#define CEILING_DIV(X, Y) ((X) - ((Y)-1) / (Y))
#endif // CEILING_DIV

#define DIGRAPH_NODE_ARRAY_SIZE(NODE_NUM) (CEILING_DIV(NODE_NUM, 8))

#define DIGRAPH_ADJ_MATRIX_SIZE(NODE_NUM)                                      \
  (DIGRAPH_NODE_ARRAY_SIZE(NODE_NUM) * DIGRAPH_NODE_ARRAY_SIZE(NODE_NUM))

/**
 * @brief Adds a directed edge from node n to node m.
 *
 * @param a Pointer to the adjacency matrix.
 * @param nodes_num Number of nodes in the graph.
 * @param n Source node.
 * @param m Destination node.
 * @return Pointer to the modified adjacency matrix.
 */
unsigned char *DiGraph_addEdge(unsigned char *a, unsigned nodes_num, unsigned n,
                               unsigned m);

/**
 * @brief Checks if there is an edge from node n to node m.
 *
 * @param a Pointer to the adjacency matrix.
 * @param nodes_num Number of nodes in the graph.
 * @param n Source node.
 * @param m Destination node.
 * @return 1 if an edge exists, 0 otherwise.
 */
int DiGraph_hasEdge(const unsigned char *a, unsigned nodes_num, unsigned n,
                    unsigned m);

/**
 * @brief Removes a directed edge from node n to node m.
 *
 * @param a Pointer to the adjacency matrix.
 * @param nodes_num Number of nodes in the graph.
 * @param n Source node.
 * @param m Destination node.
 * @return Pointer to the modified adjacency matrix.
 */
unsigned char *DiGraph_removeEdge(unsigned char *a, unsigned nodes_num,
                                  unsigned n, unsigned m);

/**
 * @brief Checks if the graph is acyclic.
 *
 * @param a Pointer to the adjacency matrix.
 * @param nodes_num Number of nodes in the graph.
 * @param buf Buffer for temporary data of size DIGRAPH_ADJ_MATRIX_SIZE
 * (nodes_num) + 2 * DIGRAPH_NODE_ARRAY_SIZE (nodes_num).
 * @return 1 if the graph is acyclic, 0 otherwise.
 */
int DiGraph_isAcyclic(const unsigned char *a, unsigned nodes_num,
                      unsigned char *buf);

/**
 * @brief Removes redundant edges to simplify the graph.
 * @note This algorithm fails if the graph is cyclic
 *
 * @param a Pointer to the adjacency matrix.
 * @param nodes_num Number of nodes in the graph.
 * @return Pointer to the simplified adjacency matrix.
 */
unsigned char *DiGraph_simplify(unsigned char *a, unsigned nodes_num);

/**
 * @brief Marks a specific node.
 *
 * @param nodes Pointer to the bitfield.
 * @param n Node to be marked.
 * @return Pointer to the updated bitfield.
 */
unsigned char *DiGraph_markNode(unsigned char *nodes, unsigned n);

/**
 * @brief Unmarks a specific node.
 *
 * @param nodes Pointer to the bitfield.
 * @param n Node to be unmarked.
 * @return Pointer to the updated bitfield.
 */
unsigned char *DiGraph_unmarkNode(unsigned char *nodes, unsigned n);

/**
 * @brief Checks if a node is marked.
 *
 * @param nodes Pointer to the bitfield.
 * @param n Node to check.
 * @return 1 if the node is marked, 0 otherwise.
 */
int DiGraph_isNodeMarked(const unsigned char *nodes, unsigned n);

#endif // DIGRAPH_H
