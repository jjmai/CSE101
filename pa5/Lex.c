/*********************************
 * Jordan Mai,jmai12
 * 2020 Spring CSE101 PA5
 * Lex.c
 * Program to sort alphabetically
 **********************************/

#include "Dictionary.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "ERROR INFILE OR OUTFILE NOT GIVEN\n");
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
  // count number of lines
  while ((lines = fgetc(infile)) != EOF) {
    if (lines == '\n') {
      count++;
    }
  }
  char array[count][255];
  fclose(infile);
  infile = fopen(argv[1], "r");
  // store each word in array
  while ((fgets(array[array_index], sizeof(array[array_index]), infile))) {
    array_index++;
  }

  Dictionary d = newDictionary(1);
  for (int i = 0; i < array_index; i++) {
    insert(d, array[i], i);
  }
  beginForward(d);
  for (int i = 0; i < size(d); i++) {
    fprintf(outfile, "%s", currentKey(d));
    next(d);
  }
  fclose(infile);
  fclose(outfile);
  freeDictionary(&d);
}
