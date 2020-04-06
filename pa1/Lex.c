#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fputs("ERROR", stderr);
    exit(1);
  }
  FILE *fp = stdin;
  char lines;
  int count = 0;
  fp = fopen(argv[1], "r");
  for (lines = getc(fp); lines != EOF; lines = getc(fp)) {
    if (lines == '\n') {
      count++;
    }
  }
  fclose(fp);
  fp = fopen(argv[1], "r");

  char array[count][20];
  int index = 0;
  while ((fscanf(fp, "%s", array[index])) != EOF) {
    index++;
  }
  FILE *fp2 = stdout;
  fp2 = fopen(argv[2], "w");
  
  List L=newList();

  for (int i = 0; i < index; i++) {
    if (length(L) == 0) {
      append(L, i);
      moveFront(L);
    } else {
      if (strcmp(array[i], array[get(L)]) < 0) {
        while (strcmp(array[i], array[get(L)]) < 0) {
          movePrev(L);
          if (get(L) == -1) {
            prepend(L, i);
            break;
          }
        }
        insertAfter(L, i);
        if (get(L) == -1) {
          moveFront(L);
        }
      } else if (strcmp(array[i], array[get(L)]) > 0) {
        while (strcmp(array[i], array[get(L)]) > 0) {
          moveNext(L);
          if (get(L) == -1) {
            append(L, i);
            break;
          }
        }
        insertBefore(L, i);
        if (get(L) == -1) {
          moveBack(L);
        }
      } else if (strcmp(array[i], array[get(L)]) == 0) {
        append(L, i);
      }
    }
}
    printList(fp2, L);
    fclose(fp2);
  }
