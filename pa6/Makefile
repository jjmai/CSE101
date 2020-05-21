#----------------------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring 2020, PA6

# Makefile for Dictionary ADT

# make				makes Order
# make DictionaryTest.c		makes Dictionary Test Client
# make clean			remove all binaries
# make infer 			checks for errors
# make format			auto format all *.c *.h
# make valgrind			checks for memory leaks
#----------------------------------------------------------------

CFLAGS = -Wall -std=c11
CC = clang $(CFLAGS)
MEMCHECK = valgrind --leak-check=full

all			:	Order

Order			:	Order.o Dictionary.o 
			$(CC) -o Order Order.o Dictionary.o -g

DictionaryTest		:	DictionaryTest.o Dictionary.o
			$(CC) -o DictionaryTest DictionaryTest.o Dictionary.o 

Order.o			:	Order.c
			$(CC) -c Order.c

DictionaryTest.o	:	DictionaryTest.c
			$(CC) -c DictionaryTest.c

Dictionary.o		:	Dictionary.c
			$(CC) -c Dictionary.c

clean			:
			rm -rf *.o Order DictionaryTest infer-out

format			:
			clang-format -i -style=file *.c *.h

infer			:
			make clean; infer-capture -- make; infer-analyze -- make
		
valgrind		:
			MEMCHECK Order

