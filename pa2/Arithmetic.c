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
  fscanf(infile, "%s", word);
  long b1 = atol(word);
  if (b1 >= 0 || b1 <= 1000000000) {
    BASE = b1;
    POWER = strlen(word) - 1;
  } else {
    fputs("ERROR base too big or too small.\n", stderr);
    exit(1);
  }
  fscanf(infile, "%s", word);
  BigInteger a = stringToBigInteger(word);
  fscanf(infile, "%s", word);
  fscanf(infile, "%s", word);
  BigInteger b = stringToBigInteger(word);

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
}
