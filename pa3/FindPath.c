#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "ERROR. infile or outfile not found.\n");
  }
  FILE *infile;
  FILE *outfile;

  infile = fopen(argv[1], "r");
  if (infile == 0) {
    printf("ERROR, file empty");
    exit(1);
  }
  outfile = fopen(argv[2], "w");

  int size = 0;
  fscanf(infile, "%d", &size);
  int num1 = 0, num2 = 0;
  Graph g = newGraph(size);
  while (fscanf(infile, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      break;
    }
    addEdge(g, num1, num2);
  }
  printGraph(outfile, g);

  while (fscanf(infile, "%d %d", &num1, &num2) != EOF) {
    if (num1 == 0 && num2 == 0) {
      break;
    }
    BFS(g, num1);
    List l = newList();
    getPath(l, g, num2);
    if (getDist(g, num2) != INF) {
      fprintf(outfile, "The distance from %d to %d is %d\n", num1, num2,
              getDist(g, num2));
    } else {
      fprintf(outfile, "The distance from %d to %d is infinity\n", num1, num2);
    }
    if (getDist(g, num2) != INF) {
      fprintf(outfile, "The shortest %d-%d path is: ", num1, num2);
      printList(outfile, l);
      fprintf(outfile, "\n");
    } else {
      fprintf(outfile, "No %d-%d path exists\n", num1, num2);
    }
    fprintf(outfile, "\n");
    freeList(&l);
  }
  fclose(infile);
  fclose(outfile);
  freeGraph(&g);
}
