#include "Graph.h"
#include "List.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "ERROR infile or outfile not found");
  }
  FILE *infile;
  FILE *outfile;

  infile = fopen(argv[1], "r");
  if (infile == 0) {
    fprintf(stderr, "ERROR INFILE EMPTY");
    exit(1);
  }
  outfile = fopen(argv[2], "w");

  int size = 0;
  fscanf(infile, "%d", &size);
  int num1 = 0, num2 = 0;
  Graph g = newGraph(size);
  // read pairs until 0 0
  while (fscanf(infile, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      break;
    }
    addArc(g, num1, num2);
  }
  fprintf(outfile, "Adjacency list representation of G:\n");
  printGraph(outfile, g);
  fprintf(outfile, "\n");

  List l = newList();
  // append order number to list
  for (int i = 1; i <= getOrder(g); i++) {
    append(l, i);
  }
  DFS(g, l);
  Graph gg = copyGraph(g);
  Graph ggg = transpose(gg);

  DFS(ggg, l);
  int count = 0;
  moveFront(l);
  // count how many SCC
  while (get(l) != -1) {
    if (getParent(ggg, get(l)) == NIL) {
      count += 1;
    }
    moveNext(l);
  }
  fprintf(outfile, "G contains %d strongly connected components:\n", count);
  int num = 1;
  // go through list to find lowest number of null parent
  for (int i = 1; i <= getOrder(ggg); i++) {
    moveFront(l);
    if (getParent(ggg, i) == NIL) {
      // iterate until i
      while (get(l) != i && get(l) != -1) {
        moveNext(l);
      }
      fprintf(outfile, "Component %d: ", num);
      num++;
      fprintf(outfile, "%d ", get(l));
      moveNext(l);
      // print until next NIL parent
      while (getParent(ggg, get(l)) != NIL && get(l) != -1) {
        fprintf(outfile, "%d ", get(l));
        moveNext(l);
      }
      fprintf(outfile, "\n");
    }
  }
  fclose(infile);
  fclose(outfile);
  freeGraph(&g);
  freeGraph(&gg);
  freeGraph(&ggg);
  freeList(&l);
}
