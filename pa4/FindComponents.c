#include "Graph.h"
#include "List.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "ERROR infile or outfile not found");
  }
  FILE *infile;
  FILE *outfile;

  infile= fopen(argv[1],"r");
  if(infile ==0) {
    fprintf(stderr,"ERROR INFILE EMPTY");
    exit(1);
   }
  outfile = fopen(argv[2],"w");

  int size =0;
  fscanf(infile,"%d",&size);
  int num1=0,num2=0;
  Graph g =newGraph(size);
  while(fscanf(infile, "%d %d",&num1, &num2) !=EOF) {
    if(num1 ==0 && num2 ==0) {
      break;
  }
  addArc(g,num1,num2);    
  }
  fprintf(outfile, "Adjacency list representation of G:\n");
  printGraph(outfile,g);
  fprintf(outfile,"\n");
}
