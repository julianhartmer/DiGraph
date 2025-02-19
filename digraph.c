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

#include "digraph.h"

#include <string.h>

unsigned char *DiGraph_addEdge(unsigned char *a, unsigned nodes_num, unsigned n,
                               unsigned m) {
  unsigned bit_nr = n * nodes_num + m;

  a[bit_nr / 8] |= (1 << (bit_nr % 8));

  return a;
}

int DiGraph_hasEdge(const unsigned char *a, unsigned nodes_num, unsigned n,
                    unsigned m) {
  unsigned bit_nr = n * nodes_num + m;

  return 0 != (a[bit_nr / 8] & (1 << (bit_nr % 8)));
}

unsigned char *DiGraph_removeEdge(unsigned char *a, unsigned nodes_num,
                                  unsigned n, unsigned m) {
  unsigned bit_nr = n * nodes_num + m;

  a[bit_nr / 8] &= ~(1 << (bit_nr % 8));

  return a;
}

int DiGraph_isAcyclic(const unsigned char *a, unsigned nodes_num,
                      unsigned char *buf) {
  unsigned n, m, i;
  unsigned char *l, *s, *a2;

  l = buf;
  s = l + DIGRAPH_NODE_ARRAY_SIZE(nodes_num);
  a2 = s + DIGRAPH_NODE_ARRAY_SIZE(nodes_num);

  memset(l, 0, DIGRAPH_NODE_ARRAY_SIZE(nodes_num));
  memset(s, 0, DIGRAPH_NODE_ARRAY_SIZE(nodes_num));
  memcpy(a2, a, DIGRAPH_ADJ_MATRIX_SIZE(nodes_num));

  // setup s with all nodes with no incoming edge
  for (n = 0; n < nodes_num; n++) {
    DiGraph_markNode(s, n);
    for (m = 0; m < nodes_num; m++) {
      if (DiGraph_hasEdge(a, nodes_num, m, n)) {
        DiGraph_unmarkNode(s, n);
        break;
      }
    }
  }

  n = 0;
  while (n < nodes_num) {
    if (DiGraph_isNodeMarked(s, n)) {
      DiGraph_unmarkNode(s, n);
      DiGraph_markNode(l, n);

      for (m = 0; m < nodes_num; m++) {
        if (DiGraph_hasEdge(a2, nodes_num, n, m)) {
          DiGraph_removeEdge(a2, nodes_num, n, m);
          DiGraph_markNode(s, m);
          for (i = 0; i < nodes_num; i++) {
            if (DiGraph_hasEdge(a2, nodes_num, i, m)) {
              DiGraph_unmarkNode(s, m);
            }
          }
        }
      }
      n = 0;
    }
    n++;
  }

  for (n = 0; n < nodes_num; n++) {
    for (m = 0; m < nodes_num; m++) {
      if (DiGraph_hasEdge(a2, nodes_num, n, m)) {
        return 0;
      }
    }
  }
  return 1;
}

unsigned char *DiGraph_simplify(unsigned char *a, unsigned nodes_num) {
  unsigned i, j, k;

  for (j = 0; j < nodes_num; j++) {
    for (i = 0; i < nodes_num; i++) {
      if (DiGraph_hasEdge(a, nodes_num, i, j)) {
        for (k = 0; k < nodes_num; k++) {
          if (DiGraph_hasEdge(a, nodes_num, i, k) &&
              DiGraph_hasEdge(a, nodes_num, k, j)) {
            DiGraph_removeEdge(a, nodes_num, i, j);
          }
        }
      }
    }
  }

  return a;
}

unsigned char *DiGraph_markNode(unsigned char *nodes, unsigned n) {
  nodes[n / 8] |= (1 << (n % 8));
  return nodes;
}

unsigned char *DiGraph_unmarkNode(unsigned char *nodes, unsigned n) {
  nodes[n / 8] &= ~(1 << (n % 8));
  return nodes;
}

int DiGraph_isNodeMarked(const unsigned char *nodes, unsigned n) {
  return nodes[n / 8] & (1 << (n % 8));
}
