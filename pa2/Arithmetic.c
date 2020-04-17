#include "BigInteger.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long POWER;
extern long BASE;
#define MAX 65536 - 1

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
  if (b1 >= 0 || b1 <= 1000000000) {
    BASE = b1;
    POWER = strlen(word) - 2;
  } else {
    fputs("ERROR base too big or too small.\n", stderr);
    exit(1);
  }
  //char word2[255];
  int ch;
  char *str;
  int len = 0;
  int size = 255;
  str = malloc(size);
  while (EOF != (ch = fgetc(infile)) && ch != '\n') {
    str[len++] = ch;
    if (len == size - 1) {
      size += size;
      str = realloc(str, size);
    }
  }
  str[len] = '\0';
  BigInteger a = stringToBigInteger(str);

  //  fscanf(infile, "%s", word2);
  // BigInteger a = stringToBigInteger(word2);
  fgets(word, 10, infile);
  // fscanf(infile, "%s", word2);
  char *str2;
  int len2 = 0;
  int size2 = 255;
  str2 = malloc(size2);
  while (EOF != (ch = fgetc(infile)) && ch != '\n') {
    str2[len2++] = ch;
    if (len2 == size2 - 1) {
      size2 += size2;
      str2 = realloc(str2, size2);
    }
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
