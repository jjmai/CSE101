#-------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA1
#
# Makefile for BigInteger ADT
#
# make			makes Arithmetic
# make Arithmetic	makes Arithmetic
# make BigIntegerTest	makes BigIntegerTest
# make clean		removes object file
# make infer		checks for errors
# make format		auto formats all *.c *.h
# make valgrind 	checks for memory leaks
# make ListClientTest	makes ListClientTest
#--------------------------------------------------


CFLAGS = -Wall -std=c11
CC=clang $(CFLAGS)

all		:	Arithmetic

Arithmetic	:	Arithmetic.o BigInteger.o List.o
		$(CC) -o Arithmetic Arithmetic.o BigInteger.o List.o -g -lm

BigIntegerTest	:	BigIntegerTest.o BigInteger.o List.o
		$(CC) -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o -lm

ListClientTest	:	ListClientTest.o ListClient.o List.o
		$(CC) -o ListClienTest ListClient.o List.o


Arithmetic.o	:	Arithmetic.c
		$(CC) -c Arithmetic.c

BigIntegerTest.o	:	BigIntegerTest.c
		$(CC) -c BigIntegerTest.c

ListClientTest.o	:	ListClientTest.c
		$(CC) -c ListClientTest.c

BigInteger.o	:	BigInteger.c List.c
		$(CC) -c BigInteger.c List.c

List.o		:	List.c
		$(CC) -c List.c

clean		:	
		rm -rf *.o Arithmetic BigIntegerTest infer-out 

format		:
		clang-format -i -style=file *.c *.h

infer 		:
		make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
		valgrind --leak-check=full Arithmetic

