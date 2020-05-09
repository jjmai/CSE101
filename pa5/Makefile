#----------------------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring 2020, PA5
#
# Makefile for Dictionary ADT
#
# make				makes Lex
# make DictionaryTest.c		makes Dictionary Test Client
# make clean			remove all binaries
# make infer 			checks for errors
# make format			auto format all *.c *.h
# make valgrind			checks for memory leaks
#----------------------------------------------------------------

CFLAGS = -Wall -std=c11
CC = clang $(CFLAGS)
MEMCHECK = valgrind --leak-check=full

all			:	Lex

Lex			:	Lex.o Dictionary.o 
			$(CC) -o Lex Lex.o Dictionary.o -g

DictionaryTest		:	DictionaryTest.o Dictionary.o
			$(CC) -o DictionaryTest DictionaryTest.o Dictionary.o 

Lex.o			:	Lex.c
			$(CC) -c Lex.c

DictionaryTest.o	:	DictionaryTest.c
			$(CC) -c DictionaryTest.c

Dictionary.o		:	Dictionary.c
			$(CC) -c Dictionary.c

clean			:
			rm -rf *.o Lex infer-out

format			:
			clang-format -i -style=file *.c *.h

infer			:
			make clean; infer-capture -- make; infer-analyze -- make
		
valgrind		:
			MEMCHECK Lex
