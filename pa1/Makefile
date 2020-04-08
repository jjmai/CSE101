#-------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA1
#
# Makefile for LIST ADT
#
# make			makes Lex
# make ListClient	makes ListClient
# make clean		removes object file
# make infer		checks for errors
# make format		auto formats all *.c *.h
# make valgrind 	checks for memory leaks
# make CheckClient	checks for memory leaks in CLient
#--------------------------------------------------

CFLAGS = -Wall -std=c11
CC=clang $(CFLAGS)

all		: 	Lex

Lex		: 	Lex.o List.o
		$(CC) -o Lex Lex.o List.o -g

ListClient	:	ListClient.o List.o
		$(CC) -o ListClient ListClient.o List.o 

Lex.o		: 	Lex.c
		$(CC) -c Lex.c

List.o		: 	List.c
		$(CC) -c List.c

clean		:
		rm -rf *.o Lex ListClient infer-out

format		:
		clang-format -i -style=file *.c *.h

infer		:
		make clean; infer-capture -- make; infer-analyze -- make 

valgrind	:
		valgrind --leak-check=full Lex

checkClient	:
		valgrind --leak-check=full ListClient

