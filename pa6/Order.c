#include "Dictionary.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "ERRPR INFILE OR OUTFILE NOT GIVEN\n");
    exit(1);
  }
  char lines;
  int count = 0;
  int array_index = 0;
  FILE *infile;
  FILE *outfile;

  infile = fopen(argv[1], "r");
  if (infile == 0) {
    fprintf(stderr, "ERROR infile empty");
    exit(1);
  }
  outfile = fopen(argv[2], "w");

  while ((lines = fgetc(infile)) != EOF) {
    if (lines == '\n') {
      count++;
    }
  }
  fclose(infile);
  infile = fopen(argv[1], "r");

  Dictionary d = newDictionary(1);

  char **ptr;
  ptr = calloc(count, sizeof(char *));
  for (int i = 0; i < count; i++) {
    ptr[i] = calloc(255, sizeof(char));
  }
  while (fgets(ptr[array_index], 255, infile)) {
    array_index++;
  }
  for (int i = 0; i < array_index; i++) {
    insert(d, ptr[i], NULL);
  }

  fprintf(outfile, "******************************************************"
                   "\nPRE-ORDER:\n*********************************************"
                   "*********\n");
  printDictionary(outfile, d, "pre");
  fprintf(outfile,"\n");
  fprintf(outfile, "******************************************************\nIN-"
                   "ORDER:\n***************************************************"
                   "***\n");
  printDictionary(outfile, d, "in");
  fprintf(outfile,"\n");
  fprintf(outfile, "******************************************************"
                   "\nPOST-ORDER:\n********************************************"
                   "**********\n");
  printDictionary(outfile, d, "post");
  fprintf(outfile,"\n");
}
