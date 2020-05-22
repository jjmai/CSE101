/*********************************************
 * Jordan Mai, jmai12
 * CSE 2020 Spring PA6
 * DictionarTest.c
 * Test client for Dictionary ADT
 *******************************************/

#include "Dictionary.h"
#include <stdio.h>

int main() {
  Dictionary A = newDictionary(1);
  Dictionary B = newDictionary(0);

  if (size(A) != 0 && size(B) != 0) {
    printf("fail size");
  }

  insert(A, "a\n", NULL);
  insert(A, "a\n", NULL);
  if (size(A) != 1) {
    printf("FAIL SIZE");
    exit(1);
  }
  insert(A, "b\n", NULL);
  insert(A, "v\n", NULL);
  insert(A, "n\n", NULL);
  insert(A, "d\n", NULL);
  insert(A, "x\n", NULL);
  insert(A, "y\n", NULL);
  insert(A, "o\n", NULL);
  insert(A, "llll\n", NULL);
  printf("GRAPH A;\n");
  printDictionary(stdout, A, "pre");

  insert(B, "z\n", NULL);
  insert(B, "z\n", NULL);
  insert(B, "z\n", NULL);
  insert(B, "z\n", NULL);
  insert(B, "zz\n", NULL);
  insert(B, "zzz\n", NULL);
  printf("GRAPH B;\n");
  printDictionary(stdout, B, "pre");

  beginForward(A);
  delete (A, currentKey(A));
  beginForward(A);
  delete (A, currentKey(A));
  beginForward(B);
  delete (B, currentKey(B));
  beginForward(B);
  delete (B, currentKey(B));
  printf("GRAPH A;\n");
  printDictionary(stdout, A, "pre");
  printf("GRAPH B;\n");
  printDictionary(stdout, B, "pre");

  if(size(A)==7 && size(B)==4){
     printf("success"); 
   }
  freeDictionary(&A);
  freeDictionary(&B);
}
