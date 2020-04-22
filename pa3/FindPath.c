#include "Graph.h"
#include "List.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  Graph g = newGraph(6);
  addEdge(g, 1, 2);
  addEdge(g, 2, 6);
  addArc(g, 6, 1);
  printGraph(stdout, g);
  BFS(g, 1);
}
