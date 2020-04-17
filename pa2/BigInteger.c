#include "BigInteger.h"
#include "List.h"
#include <inttypes.h>
#include <stdbool.h>
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
  b->carry = 0;
  b->L = newList();

  return b;
}

void freeBigInteger(BigInteger *pN) {
  if (pN != NULL && *pN != NULL) {
    freeList(&(*pN)->L);
    free(*pN);
  }
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

  if (front(A->L) > front(B->L))
    return 1;
  if (front(A->L) < front(B->L))
    return -1;

  if (front(A->L) == front(B->L))
    return 0;
  exit(1);
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
  N->carry = 0;
  N->sign = 0;
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
  int neg = 0, count2 = 0;
  int count = POWER - 1;

  if (s[0] == '-') {
    b->sign = -1;
    neg++;
  } else if (s[0] == '+') {
    b->sign = 1;
    neg++
  } else {
    b->sign = 1;
  }

  for (int i = strlen(s) - 1; i >= neg; i--) {
    auex = s[i];

    temp[count] = auex;
    if (count == 0) {
      prepend(b->L, atol(temp));
      count = POWER - 1;
      count2 = 0;
    } else {
      count--;
      count2++;
    }
  }
  char temp2[POWER];
  for (int i = 0; i < count2; i++) {
    if (i == 0) {
      auex = s[i];
      temp2[i] = s[i];
      prepend(b->L, atol(temp2));
    } else {
      moveFront(b->L);
      auex = s[i];
      temp2[i] = s[i];
      insertAfter(b->L, atol(temp2));
    }
  }
  moveFront(b->L);
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

void add(BigInteger S, BigInteger A, BigInteger B) {
  BigInteger AA = copy(A);
  BigInteger BB = copy(B);
  makeZero(S);

  if ((AA->sign == 1 && BB->sign == -1)) {
    negate(BB);
    subtract(S, AA, BB);
  } else if (AA->sign == -1 && BB->sign == 1) {
    negate(AA);
    subtract(S, BB, AA);

  } else {
    int carry = 0, temp = 0, a = 0, b = 0;
    moveBack(AA->L);
    moveBack(BB->L);
    temp = length(AA->L) >= length(BB->L) ? length(AA->L) : length(BB->L);

    for (int i = 0; i < temp; i++) {
      int ab = 0;
      a = l_index(AA->L) != -1 ? get(AA->L) : EMPTY;
      b = l_index(BB->L) != -1 ? get(BB->L) : EMPTY;

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
      if (get(AA->L) == EMPTY) {
        a = EMPTY;
      } else {
        movePrev(AA->L);
      }
      if (get(BB->L) == EMPTY) {
        b = EMPTY;
      } else {
        movePrev(BB->L);
      }
      carry = 0;
    }
    if (S->carry == 1) {
      S->carry = 0;
      prepend(S->L, 1);
    }
    if (AA->sign == -1 && BB->sign == -1) {
      S->sign = -1;
    } else {
      S->sign = 1;
    }
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

void subtract(BigInteger D, BigInteger A, BigInteger B) {
  BigInteger AA = copy(A);
  BigInteger BB = copy(B);
  makeZero(D);
  negate(BB);
  if ((sign(AA) == 1 && sign(BB) == 1) || (sign(AA) == -1 && sign(BB) == -1)) {
    add(D, AA, BB);
  } else {
    if (compare(A, B) == -1) {
      AA = copy(B);
      BB = copy(A);
      D->sign = -1;
    } else {
      AA = copy(A);
      BB = copy(B);
      D->sign = 1;
    }
    negate(BB);

    int carry = 0, temp = 0, a = 0, b = 0;

    moveBack(AA->L);
    moveBack(BB->L);
    temp = length(AA->L) >= length(BB->L) ? length(AA->L) : length(BB->L);

    for (int i = 0; i < temp; i++) {
      int ab = 0;
      a = l_index(AA->L) != -1 ? get(AA->L) : EMPTY;
      b = l_index(BB->L) != -1 ? get(BB->L) : EMPTY;

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
      if (i > 0 && D->carry == -1) {
        ab -= 1;
        D->carry = 0;
      }

      if (ab < 0) {
        ab += BASE;
        carry = -1;
      }

      prepend(D->L, ab);
      if (carry == -1) {
        D->carry = -1;
      }
      if (get(AA->L) == EMPTY) {
        a = EMPTY;
      } else {
        movePrev(AA->L);
      }
      if (get(BB->L) == EMPTY) {
        b = EMPTY;
      } else {
        movePrev(BB->L);
      }
      carry = 0;
    }
    if (D->carry == -1) {
      D->sign = -1;
    }
  }
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
  int a = 0, b = 0, ab = 0, carry = 0, temp = 0;
  moveBack(AA->L);
  moveBack(BB->L);

  BigInteger big, small;
  temp = length(AA->L) <= length(BB->L) ? length(AA->L) : length(BB->L);

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
    a = l_index(big->L) != EMPTY ? get(big->L) : EMPTY;
    b = l_index(small->L) != EMPTY ? get(small->L) : EMPTY;

    while (get(big->L) != EMPTY) {
      a = get(big->L);
      if (b == EMPTY) {
        b = 1;
        ab *= b;
      } else {
        ab = a * b;
      }

      if (b_temp->carry > 0) {
        ab += b_temp->carry;
        b_temp->carry = 0;
      }

      if (ab >= BASE) {
        carry = ab / BASE;
        ab -= carry * BASE;
        b_temp->carry = carry;
      }

      prepend(b_temp->L, ab);
      movePrev(big->L);
    }
    if (b_temp->carry > 0) {
      prepend(b_temp->L, b_temp->carry);
      b_temp->carry = 0;
    }
    for (int j = 0; j < i; j++) {
      append(b_temp->L, 0);
    }
    movePrev(small->L);
    moveBack(big->L);
    add(P, P, b_temp);
  }
  P->sign = sign(AA) * sign(BB);
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
  if (sign(N) == -1) {
    fprintf(out, "%s", "-");
  }
  int count = 1;
  bool front = true;
  moveFront(N->L);
  while (get(N->L) != EMPTY) {
    count = 1;
    if (get(N->L) < BASE / 10) {
      while (count < BASE / 10 && front == false) {
        fprintf(out, "%d", 0);
        count *= 10;
      }
    }
    if (get(N->L) != 0) {
      front = false;
    }
    if (front == false) {
      fprintf(out, "%ld", get(N->L));
    }
    moveNext(N->L);
  }
  if (front == true) {
    fprintf(out, "%d", 0);
  }
  fprintf(out, "%s", "\n\n");
}
