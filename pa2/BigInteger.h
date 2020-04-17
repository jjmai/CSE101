#include <stdio.h>
#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

typedef struct BigIntegerObj *BigInteger;

BigInteger newBigInteger();

void freeBigInteger(BigInteger *pN);

int sign(BigInteger N);

int compare(BigInteger A, BigInteger B);

int equals(BigInteger A, BigInteger B);

void makeZero(BigInteger N);

BigInteger stringToBigInteger(char *s);

BigInteger copy(BigInteger N);

void add(BigInteger S, BigInteger A, BigInteger B);

BigInteger sum(BigInteger A, BigInteger B);

void subtract(BigInteger D, BigInteger A, BigInteger B);

BigInteger diff(BigInteger A, BigInteger B);

void multiply(BigInteger P, BigInteger A, BigInteger B);

void printBigInteger(FILE *out, BigInteger N);

BigInteger prod(BigInteger A, BigInteger B);
#endif
