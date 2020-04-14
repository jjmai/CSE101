CFLAGS = -Wall -std=c11
CC=clang $(CFLAGS)

all		:	Arithmetic

Arithmetic	:	Arithmetic.o BigInteger.o List.o
		$(CC) -o Arithmetic Arithmetic.o BigInteger.o List.o -g

Arithmetic.o	:	Arithmetic.c
		$(CC) -c Arithmetic.c

BigInteger.o	:	BigInteger.c List.c
		$(CC) -c BigInteger.c List.c

List.o		:	List.c
		$(CC) -c List.c

clean		:	
		rm -rf *.o Arithmetic 

format		:
		clang-format -i -style=file *.c *.h



