/******************************************
 * Jordan Mai, jmai12
 * CSE101 2020 Spring, PA5
 * Test Client for Dictionary ADT
 *********************************************/

#include "Dictionary.h"
#include <stdio.h>

int main() {
  Dictionary A = newDictionary(0);
  Dictionary B = newDictionary(1);

  char *word[] = {"z", "o", "p", "a", "n"};
  char *word2[] = {"l", "o", "p", "l", "p"};

  for (int i = 0; i < 5; i++) {
    insert(A, word[i], i);
  }
  printDictionary(stdout, A);
  if (size(A) == 5) {
    printf("size of Dic A is 5\n");
  }
  for (int i = 0; i < 5; i++) {
    insert(B, word2[i], i);
  }
  printDictionary(stdout, B);
  if (size(B) == 5) {
    printf("size of Dic B is 5\n");
  }
  printf("REVERSE:\n");

  beginReverse(A);
  for (int i = 0; i < size(A); i++) {
    printf("%s %d \n", currentKey(A), currentVal(A));
    prev(A);
  }
  printf("size of Dic A is %d\n", size(A));
  beginReverse(B);
  for (int i = 0; i < size(B); i++) {
    printf("%s %d \n", currentKey(B), currentVal(B));
    prev(B);
  }
  printf("size of Dic B is %d\n", size(B));

  printf("DELETING\n\n");

  for (int i = 0; i < 5; i += 2) {
    delete (A, word[i]);
    delete (B, word2[i]);
  }
  printf("Graph A\n");
  printDictionary(stdout, A);
  printf("GRaph B\n");
  printDictionary(stdout, B);
  if (size(A) == 2 && size(B) == 2) {
    printf("YES both dic is size 2\n");
  }
  insert(A, "a", 6);
  if (size(A) == 2) {
    printf("success no duplicates\n");
  }
  makeEmpty(A);
  makeEmpty(B);
  if (size(A) == 0 && size(B) == 0) {
    printf("Both Dict empty\n");
  }
  freeDictionary(&A);
  freeDictionary(&B);
}
