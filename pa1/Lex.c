/******************************
 * Jordan Mai, jmai12
 * 2020 Spring CES101 PA1
 * Lex.c
 * Program to sort aplhabetically
 ******************************/

#include "List.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // exit if input and out file not specified
  if (argc != 3) {
    fputs("ERROR, infile or outfile not given\n", stderr);
    exit(1);
  }

  char lines;             // variable to sotre '\n'
  int count = 0;          // variable to store line count
  char array[count][255]; // 2d array store strings
  int array_index = 0;    // index for array

  FILE *fp;
  FILE *fp2;

  fp2 = fopen(argv[2], "w"); // open output file write

  fp = fopen(argv[1], "r"); // open input file read
  // loop to check number of newlines
  for (lines = getc(fp); lines != EOF; lines = getc(fp)) {
    if (lines == '\n') {
      count++;
    }
  }
  fclose(fp);
  fp = fopen(argv[1], "r"); // reopen input file to read again

  // read in line by line from file
  while ((fgets(array[array_index], sizeof(array[array_index]), fp))) {
    array_index++;
  }

  List L = newList();

  for (int i = 0; i < array_index; i++) {
    // if first element n List, then just add it in
    if (length(L) == 0) {
      append(L, i);
      moveFront(L);
    } else {
      // if current string is before cursor element
      if (strcmp(array[i], array[get(L)]) < 0) {
        while (strcmp(array[i], array[get(L)]) < 0) {
          movePrev(L);
          if (index(L) == -1) {
            prepend(L, i);
            break;
          }
        }
        insertAfter(L, i);
        if (index(L) == -1) {
          moveFront(L);
        }
      } else if (strcmp(array[i], array[get(L)]) > 0) { // if after element
        while (strcmp(array[i], array[get(L)]) > 0) {
          moveNext(L);
          if (index(L) == -1) {
            append(L, i);
            break;
          }
        }
        insertBefore(L, i);
        if (index(L) == -1) {
          moveBack(L);
        }
      } else if (strcmp(array[i], array[get(L)]) == 0) {
        append(L, i);
      }
    }
  }
  // print the List
  moveFront(L);
  for (int i = 0; i < array_index; i++) {
    fprintf(fp2, "%s", array[get(L)]);
    moveNext(L);
  }
  fclose(fp);
  fclose(fp2);
  freeList(&L);
}
