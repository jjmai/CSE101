#-------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA4
# 
# Makefile for Graph ADT
# 
# make			makes FindComponents
# make FindComponents	makes FindComponents
# make GraphTest	makes GraphTest
# make clean		removes object file
# make infer		checks for errors
# make format		auto formats all *.c *.h
# make valgrind 	checks for memory leaks
#--------------------------------------------------

CFLAGS = -Wall -std=c11
CC = clang $(CFLAGS)

all		:	FindComponents

FindComponents	:	FindComponents.o Graph.o List.o
		$(CC) -o FindComponents FindComponents.o Graph.o List.o -g

GraphTest	:	GraphTest.o Graph.o List.o
		$(CC) -o GraphTest GraphTest.o Graph.o List.o

FindComponents.o	:	FindComponents.c
			$(CC) -c FindComponents.c

GraphTest.o	:	GraphTest.c
		$(CC) -c GraphTest.c

Graph.o		:	Graph.c List.c
		$(CC) -c Graph.c List.c

List.o		:	List.c
		$(CC) -c List.c

clean		:
		rm -rf *.o FindComponents GraphTest infer-out

format		:
		clang-format -i -style=file *.c *.h

infer		:
		make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
		$(CC) valgrind --leak-check=full FindComponents
