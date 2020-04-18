#include "BigInteger.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long POWER;
extern long BASE;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fputs("ERROR, infile or outfile missing.\n", stderr);
    exit(1);
  }
  FILE *infile;
  FILE *outfile;
  infile = fopen(argv[1], "r");
  outfile = fopen(argv[2], "w");

  char word[255];
  fgets(word, 10, infile);
  long b1 = atol(word);
  //BASE = b1;
  //POWER = strlen(word) - 2;
  int ch;
  char *str;
  int len = 0;
  str = malloc(b1+1);
  while (EOF != (ch = fgetc(infile)) && ch != '\n') {
    str[len++] = ch;
  }
  str[len] = '\0';
  BigInteger a = stringToBigInteger(str);
  fgets(word, 10, infile);
  b1=atol(word);
  char *str2;
  int len2 = 0;
  str2 = malloc(b1+1);
  while (EOF != (ch = fgetc(infile)) && ch != '\n') {
    str2[len2++] = ch;
  }
  str2[len2] = '\0';

  BigInteger b = stringToBigInteger(str2);

  printBigInteger(outfile, a);
  printBigInteger(outfile, b);
  
  printBigInteger(outfile, sum(a, b));
  printBigInteger(outfile, diff(a, b));
  printBigInteger(outfile, diff(a, a));
  BigInteger aa = prod(a, stringToBigInteger("3"));
  BigInteger bb = prod(b, stringToBigInteger("2"));
  printBigInteger(outfile, diff(aa, bb));
  printBigInteger(outfile, prod(a, b));
  printBigInteger(outfile, prod(a, a));
  printBigInteger(outfile, prod(b, b));
  aa = (prod(a, prod(a, prod(a, a))));
  bb = prod(b, prod(b, prod(b, prod(b, b))));
  BigInteger aaa = prod(aa, stringToBigInteger("9"));
  BigInteger bbb = prod(bb, stringToBigInteger("16"));
  printBigInteger(outfile, sum(aaa, bbb));

  fclose(infile);
  fclose(outfile);
  // freeBigInteger(&a);
  // freeBigInteger(&b);
  // freeBigInteger(&aa);
  // freeBigInteger(&bb);
}
