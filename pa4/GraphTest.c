/*************************************
 * Jordan Mai, jmai12
 * 2020 Spring CSE101 PA4
 * GraphTest.c
 * Test CLient
 ************************************/ 

#include "Graph.h"
#include "List.h"
#include <stdio.h>

int main() {
  Graph g = newGraph(8);
  List l = newList();
  if (getDiscover(g, 2) != UNDEF) {
    printf("1");
    exit(1);
  }
  if (getDiscover(g, 0) != UNDEF) {
    printf("1");
    exit(1);
  }
  addArc(g, 1, 2);
  addArc(g, 2, 3);
  addArc(g, 2, 5);
  addArc(g, 2, 6);
  addArc(g, 3, 4);
  addArc(g, 3, 7);
  addArc(g, 4, 3);
  addArc(g, 5, 1);
  addArc(g, 5, 6);
  addArc(g, 6, 7);
  addArc(g, 7, 6);
  addArc(g, 7, 8);
  addArc(g, 8, 8);
  printGraph(stdout, g);
  if (getOrder(g) == 8) {
    printf("Order is 8\n");
  }
  for (int i = 1; i <= getOrder(g); i++) {
    append(l, i);
  }
  DFS(g, l);
  printList(stdout, l);
  printf("\n");
  if (getFinish(g, 1) == 16) {
    printf("1 finish time is 16\n");
  }
  Graph gg = copyGraph(g);
  Graph ggg = transpose(gg);
  printGraph(stdout, ggg);
  DFS(ggg, l);
  printList(stdout, l);
  printf("\n");
  if (getFinish(ggg, 8) == 16) {
    printf("8 finish time is 16\n");
  }
  int count = 0;
  moveFront(l);
  while (get(l) != -1) {
    if (getParent(ggg, get(l)) == NIL) {
      count += 1;
    }
    moveNext(l);
  }
  if (count == 4) {
    printf("4 SCC\n");
  }
  count=0;
  moveFront(l);
  while(get(l)!=-1) {
   if(getParent(ggg,get(l))==NIL) {
     count+=1;
    }
   moveNext(l);
  }
  if(count ==4) {
   printf("4 NIL parents\n");
  }
  freeGraph(&g);
  freeGraph(&gg);
  freeGraph(&ggg);
  freeList(&l); 
}
