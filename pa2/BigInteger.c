/******************************
 *  * Jordan Mai, jmai12
 *  * 2020 Spring CES101 PA2
 *  * BigInteger.c
 *  * BigInteger ADT
 *******************************/

#include "BigInteger.h"
#include "List.h"
#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1 // determine if node is NULL
long POWER = 1;
long BASE = 10;

typedef struct BigIntegerObj {
  int sign;
  int carry;
  List L;
} BigIntegerObj;

// create new BigInt
BigInteger newBigInteger() {
  BigInteger b = malloc(sizeof(BigIntegerObj));
  assert(b);
  b->sign = 0;
  // b->carry = 0;
  b->L = newList();
  return b;
}

void freeBigInteger(BigInteger *pN) {
  if (pN != NULL && *pN != NULL) {
    freeList(&(*pN)->L);
    free(*pN);
    *pN = NULL;
  }
}

// sign value
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

// return 1 if A>B, -1 if A<B, 0 if equal
int compare(BigInteger A, BigInteger B) {
  if (sign(A) == 1 && sign(B) == -1)
    return 1;
  if (sign(A) == -1 && sign(B) == 1)
    return -1;

  if (length(A->L) > length(B->L) && sign(A) == 1 && sign(B) == 1)
    return 1;
  if (length(A->L) < length(B->L) && sign(A) == 1 && sign(B) == 1)
    return -1;

  if (length(A->L) > length(B->L) && sign(A) == -1 && sign(B) == -1)
    return -1;
  if (length(A->L) < length(B->L) && sign(A) == -1 && sign(B) == -1)
    return 1;
  moveFront(A->L);
  moveFront(B->L);
  while (get(A->L) != EMPTY && get(B->L) != EMPTY) {
    if (get(A->L) > (get(B->L))) {
      return 1;
    }
    if (get(A->L) < get(B->L)) {
      return -1;
    }
    moveNext(A->L);
    moveNext(B->L);
  }

  return 0;

  return 0;
}

int equals(BigInteger A, BigInteger B) {
  if (compare(A, B) == 0) {
    return 1;
  } else {
    return 0;
  }
}

void makeZero(BigInteger N) {
  clear(N->L);
  // N->carry = 0;
  N->sign = 0;
}

void negate(BigInteger N) {
  if (N->sign == -1) {
    N->sign = 1;
  } else if (N->sign == 1) {
    N->sign = -1;
  }
}

// converts string to a long of bigInt
BigInteger stringToBigInteger(char *s) {
  BigInteger b = newBigInteger();
  char auex;
  char temp[POWER];
  for (int i = 0; i < POWER + 1; i++) {
    temp[i] = '\0';
  }
  int neg = 0, count2 = 0;
  int count = POWER - 1;
  long num = 0;

  // if there is a sign in front, increment counter
  // so we don't push that in a node
  if (s[0] == '-') {
    b->sign = -1;
    neg++;
  } else if (s[0] == '+') {
    b->sign = 1;
    neg++;
  } else {
    b->sign = 1;
  }
  // place in node based on BASE #
  for (int i = strlen(s) - 1; i >= neg; i--) {
    auex = s[i];
    temp[count] = auex;
    if (count == 0) {
      num = atol(temp);
      prepend(b->L, num);
      count = POWER - 1;
      count2 = 0;
    } else {
      count--;
      count2++;
    }
  }
  // prepend remainders
  char temp2[POWER + 1];
  for (int i = 0; i < POWER + 1; i++) {
    temp2[i] = '\0';
  }
  long count3 = 0;
  for (long i = neg; i < count2 + neg; i++) {
    auex = s[i];
    temp2[count3++] = auex;
  }
  num = atol(temp2);
  prepend(b->L, num);
  moveFront(b->L);
  // strip leading zeros
  while (get(b->L) == 0) {
    deleteFront(b->L);
    moveFront(b->L);
  }

  return b;
}

BigInteger copy(BigInteger N) {
  BigInteger b = newBigInteger();
  b->L = copyList(N->L);
  b->sign = sign(N);

  return b;
}
// add function
void add(BigInteger S, BigInteger A, BigInteger B) {
  BigInteger AA = copy(A);
  BigInteger BB = copy(B);
  makeZero(S);
  // if there is negative, call subtract
  if ((AA->sign == 1 && BB->sign == -1)) {
    negate(BB);
    subtract(S, AA, BB);
  } else if (AA->sign == -1 && BB->sign == 1) {
    negate(AA);
    subtract(S, BB, AA);
  } else {
    long carry = 0, temp = 0, a = 0, b = 0;
    moveBack(AA->L);
    moveBack(BB->L);
    // need longest length to add
    temp = length(AA->L) >= length(BB->L) ? length(AA->L) : length(BB->L);

    for (long i = 0; i < temp; i++) {
      long ab = 0;
      a = index(AA->L) != -1 ? get(AA->L) : EMPTY;
      b = index(BB->L) != -1 ? get(BB->L) : EMPTY;

      // if a node is empty, just add 0,else add
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
      // if there is overflow, add 1
      if (i > 0 && carry == 1) {
        ab += 1;
        carry = 0;
      }
      // only store based on POWER
      if (ab >= BASE) {
        ab -= BASE;
        carry = 1;
      }
      prepend(S->L, ab);

      if (get(AA->L) != EMPTY) {
        movePrev(AA->L);
      }
      if (get(BB->L) != EMPTY) {
        movePrev(BB->L);
      }
    }
    if (carry == 1) {
      carry = 0;
      prepend(S->L, 1);
    }
    // change signs
    if (AA->sign == -1 && BB->sign == -1) {
      S->sign = -1;
    } else {
      S->sign = 1;
    }
  }
  freeBigInteger(&AA);
  freeBigInteger(&BB);
}
// returns the sum of add
BigInteger sum(BigInteger A, BigInteger B) {
  if (A && B) {
    BigInteger b = newBigInteger();
    add(b, A, B);
    return b;
  }
  return NULL;
}
// minus
void subtract(BigInteger D, BigInteger A, BigInteger B) {
  BigInteger AA = copy(A);
  BigInteger BB = copy(B);
  makeZero(D);
  negate(BB);
  // if both A B same signs then add
  if ((sign(AA) == 1 && sign(BB) == 1) || (sign(AA) == -1 && sign(BB) == -1)) {
    add(D, AA, BB);
  } else {
    negate(BB);
    // compare AA,BB and make the bigger number AA
    if (compare(AA, BB) == -1) {
      AA = copy(B);
      BB = copy(A);
      D->sign = -1;
    } else {
      AA = copy(A);
      BB = copy(B);
      D->sign = 1;
    }
    negate(BB);

    long carry = 0, temp = 0, a = 0, b = 0;

    moveBack(AA->L);
    moveBack(BB->L);
    temp = length(AA->L) >= length(BB->L) ? length(AA->L) : length(BB->L);

    for (long i = 0; i < temp; i++) {
      long ab = 0;
      a = index(AA->L) != -1 ? get(AA->L) : EMPTY;
      b = index(BB->L) != -1 ? get(BB->L) : EMPTY;
      // add zero if EMPTY
      if (a == EMPTY) {
        ab += 0;
      } else {
        if (sign(AA) == 1) {
          ab += a;
        } else {
          ab -= a;
        }
      }
      if (b == EMPTY) {
        ab += 0;
      } else {
        if (sign(BB) == 1) {
          ab += b;
        } else {
          ab -= b;
        }
      }
      if (i > 0 && carry == -1) {
        ab -= 1;
        carry = 0;
      }

      if (ab < 0) {
        ab += BASE;
        carry = -1;
      }

      prepend(D->L, ab);

      if (get(AA->L) != EMPTY) {
        movePrev(AA->L);
      }
      if (get(BB->L) != EMPTY) {
        movePrev(BB->L);
      }
    }
    if (carry == -1) {
      D->sign = -1;
      carry = 0;
    }
  }
  // if the value is zero, set sign to 0

  moveFront(D->L);
  if (front(D->L) == 0) {
    bool zero = true;
    while (get(D->L) != EMPTY) {
      if (get(D->L) != 0) {
        zero = false;
        break;
      }
      zero = true;
      moveNext(D->L);
    }
    if (zero == true) {
      D->sign = 0;
    }
  }

  freeBigInteger(&AA);
  freeBigInteger(&BB);
}

BigInteger diff(BigInteger A, BigInteger B) {
  if (A && B) {
    BigInteger b = newBigInteger();
    subtract(b, A, B);
  
    return b;
  }
  return NULL;
}

void multiply(BigInteger P, BigInteger A, BigInteger B) {
  BigInteger AA = copy(A);
  BigInteger BB = copy(B);
  makeZero(P);

  P->sign = sign(AA) * sign(BB);
  long a = 0, b = 0, ab = 0, carry = 0, temp = 0;
  moveBack(AA->L);
  moveBack(BB->L);

  BigInteger big, small;
  temp = length(AA->L) <= length(BB->L) ? length(AA->L) : length(BB->L);

  // set the bigger number to big
  if (length(AA->L) >= length(BB->L)) {
    big = AA;
    small = BB;
  } else {
    big = BB;
    small = AA;
  }

  moveBack(big->L);
  moveBack(small->L);
  BigInteger b_temp;

  for (int i = 0; i < temp; i++) {
    b_temp = newBigInteger();
    ab = 0, carry = 0;
    a = index(big->L) != EMPTY ? get(big->L) : EMPTY;
    b = index(small->L) != EMPTY ? get(small->L) : EMPTY;

    while (get(big->L) != EMPTY) {
      a = get(big->L);
      if (b == EMPTY) {
        b = 1;
        ab *= b;
      } else {
        ab = a * b;
      }

      if (carry > 0) {
        ab += carry;
        carry = 0;
      }

      if (ab >= BASE) {
        carry = ab / BASE;
        ab -= carry * BASE;
      }
      prepend(b_temp->L, ab);
      movePrev(big->L);
    }
    if (carry > 0) {
      prepend(b_temp->L, carry);
      carry = 0;
    }
    // place a zero at end after every increment
    for (int j = 0; j < i; j++) {
      append(b_temp->L, 0);
    }
    movePrev(small->L);
    moveBack(big->L);
    // add after every multiplication
    add(P, P, b_temp);
  }
  P->sign = sign(AA) * sign(BB);
  freeBigInteger(&AA);
  freeBigInteger(&BB);
  freeBigInteger(&b_temp);
}

BigInteger prod(BigInteger A, BigInteger B) {
  if (A && B) {
    BigInteger b = newBigInteger();
    multiply(b, A, B);
    return b;
  }
  exit(1);
}

void printBigInteger(FILE *out, BigInteger N) {
  // printList(stdout, N->L);
  if (sign(N) == -1) {
    fprintf(out, "%s", "-");
  }

  int count = 1;
  bool front = true;
  moveFront(N->L);
  while (get(N->L) != EMPTY) {
    count = 1;
    // if number in node not length of POWER
    // prepend a zero to fill in
    if (get(N->L) < BASE / 10) {
      while (count < BASE / 10 && front == false) {
        fprintf(out, "%d", 0);
        count *= 10;
      }
    }
    // if zero then do nothing
    if (get(N->L) != 0) {
      front = false;
    }
    if (front == false) {
      fprintf(out, "%ld", get(N->L));
    }
    moveNext(N->L);
  }
  // only print one zero if answer is zero
  if (front == true) {
    fprintf(out, "%d", 0);
  }

  fprintf(out, "%s", "\n\n");
}
