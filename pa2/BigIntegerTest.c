#include "BigInteger.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  BigInteger a = stringToBigInteger("+111122223333");
  BigInteger b = stringToBigInteger("+222211110000");
  BigInteger c = newBigInteger();
  BigInteger d = stringToBigInteger("+333333333333");
  printBigInteger(stdout, a);
  printBigInteger(stdout, b);
  add(c, a, b);
  printBigInteger(stdout, c);
  if (!equals(c, d)) {
    printf("1");
  }
  freeBigInteger(&b);
  freeBigInteger(&d);
  b = stringToBigInteger("-111122223333");
  add(c, a, b);
  printBigInteger(stdout, c);
  if (sign(c) != 0) {
    printf("2\n");
  }
  freeBigInteger(&b);
  b = stringToBigInteger("-110122223333");
  add(c, a, b);
  printBigInteger(stdout, c);
  if (sign(c) != 1) {
    printf("3");
  }

  freeBigInteger(&b);
  b = stringToBigInteger("-112122223333");
  add(c, a, b);
  printBigInteger(stdout, c);
  if (sign(c) != -1)
    printf("4");

  freeBigInteger(&a);
  a = stringToBigInteger("-221211110000");
  d = stringToBigInteger("-333333333333");
  add(c, a, b);
  printBigInteger(stdout, c);
  if (!equals(c, d))
    printf("5");

  freeBigInteger(&b);
  freeBigInteger(&c);
  freeBigInteger(&a);
  a = stringToBigInteger("-111122223333");
  b = stringToBigInteger("-112122223333");
  c = diff(a, b);
  if (sign(c) != 1)
    printf("2");

  printBigInteger(stdout,prod(a,b));
}
