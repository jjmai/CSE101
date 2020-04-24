/**************************
 * * Jordan Mai,jmai12
 * * 2020 Spring CSE101 PA3
 * * GraphTest.c
 * * Client for GraphTest
 ***************************/

#include "Graph.h"
#include "List.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  Graph g = newGraph(10);
  addEdge(g, 1, 2);
  addEdge(g, 2, 6);
  addArc(g, 6, 1);
  addArc(g, 6, 3);
  addEdge(g, 3, 2);
  addEdge(g, 4, 5);
  addEdge(g, 9, 2);
  addEdge(g, 10, 5);

  printGraph(stdout, g);

  BFS(g, 1);
  printf("Source = %d \n", getSource(g));

  printf("Size = %d \n", getSize(g));
  printf("Distance from 1 to 6 = %d \n", getDist(g, 6));

  List l = newList();
  getPath(l, g, 6);
  printf("Path from 1-6 = ");
  printList(stdout, l);
  printf("\n\n");
  makeNull(g);
  printf("Order %d should be same\n",getOrder(g));
  clear(l);
  if (getSource(g) != 0) {
    printf("error on getsource after delete");
  }

  addEdge(g, 1, 5);
  addEdge(g, 2, 3);
  addEdge(g, 9, 4);
  addEdge(g, 10, 2);
  addEdge(g, 1, 7);
  addEdge(g, 7, 8);
  addEdge(g, 6, 5);

  printGraph(stdout, g);
  BFS(g, 1);

  printf("Source = %d \n", getSource(g));

  printf("Size = %d \n", getSize(g));
  printf("Distance from 1 to 6 = %d \n", getDist(g, 10));

  getPath(l, g, 2);
  printf("Path from 1-2 = ");
  printList(stdout, l);
  printf("\n");

  freeList(&l);
  freeGraph(&g);
}
