#include "BigInteger.h"
#include "List.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
long POWER;
long BASE;

typedef struct BigIntegerObj {
  int sign;
  int carry;
  List L;

} BigIntegerObj;

BigInteger newBigInteger() {
  BigInteger b = malloc(sizeof(BigIntegerObj));
  b->sign = 0;
  b->L = newList();

  return b;
}

int sign(BigInteger N) {
  if (N) {
    if (N->sign == -1) {
      return -1;
    } else if (N->sign == 1) {
      return 1;
    } else {
      return 0;
    }
  }
  exit(1);
}

void negate(BigInteger N) {
  if (N->sign == -1) {
    N->sign = 1;
  } else if (N->sign == 1) {
    N->sign = -1;
  }
}

BigInteger stringToBigInteger(char *s) {
  BigInteger b = newBigInteger();
  char auex;
  char temp[POWER];
  char temp1[POWER];
  int neg = 0, count = POWER - 1;

  if (s[0] == '-') {
    b->sign = -1;
    neg++;
  } else {
    b->sign = 1;
  }

  for (int i = strlen(s) - 1; i >= neg; i--) {
    auex = s[i];

    temp[count] = auex;
    if (count == 0) {
      prepend(b->L, atol(temp));
      count = POWER - 1;
    } else {
      count--;
    }
  }
  char temp2[POWER];
  if (count > 0) {
    for (int i = neg; i < POWER - count; i++) {
      auex = s[i];
      temp2[i] = auex;
    }
    prepend(b->L, atol(temp2));
  }
  printList(stdout, b->L);
  printf("\n");

  return b;
}

BigInteger copy(BigInteger N) {
  BigInteger b = newBigInteger();
  b->L = copyList(N->L);
  printList(stdout, b->L);

  return b;
}

void add(BigInteger S, BigInteger A, BigInteger B) {

  if ((A->sign == 1 && B->sign == 1) || (A->sign == -1 && B->sign == -1)) {
    int carry = 0, temp = 0, a = 0, b = 0;

    moveBack(A->L);
    moveBack(B->L);
    temp = length(A->L) >= length(B->L) ? length(A->L) : length(B->L);

    for (int i = 0; i < temp; i++) {
      int ab = 0;
      a = l_index(A->L) != -1 ? get(A->L) : EMPTY;
      b = l_index(B->L) != -1 ? get(B->L) : EMPTY;
      if (a == EMPTY) {
        ab += 0;
      } else {
        ab += a;
      }
      if (b == EMPTY) {
        ab += 0;
      } else {
        ab += b;
      }

      if (i > 0 && S->carry == 1) {
        ab += 1;
        S->carry = 0;
      }

      if (ab >= BASE) {
        ab -= BASE;
        carry = 1;
      }
      prepend(S->L, ab);
      if (carry == 1) {
        S->carry = 1;
      }
      if (get(A->L) == EMPTY) {
        a = EMPTY;
      } else {
        movePrev(A->L);
      }
      if (get(B->L) == EMPTY) {
        b = EMPTY;
      } else {
        movePrev(B->L);
      }
      carry = 0;
    }
    if (S->carry == 1) {
      S->carry = 0;
      prepend(S->L, 1);
    }
    printList(stdout, S->L);
  }
}

BigInteger sum(BigInteger A, BigInteger B) {
  if (A && B) {
    BigInteger b = newBigInteger();
    add(b, A, B);
    return b;
  }
  return NULL;
}
