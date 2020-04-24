#-------------------------------------------------
# Jordan Mai, jmai12
# # CSE101 Spring, PA3
# #
# # Makefile for Graph ADT
# #
# # make		makes FindPath
# # make FindPath	makes FindPath
# # make GraphTest	makes GraphTest
# # make clean		removes object file
# # make infer		checks for errors
# # make format		auto formats all *.c *.h
# # make valgrind 	checks for memory leaks
# #--------------------------------------------------

CFLAGS = -Wall -std=c11
CC = clang $(CFLAGS)
MEMCHECK = valgrind --leak-check=full

all		:	FindPath

FindPath	:	FindPath.o Graph.o List.o
		$(CC) -o FindPath FindPath.o Graph.o List.o -g

GraphTest	:	GraphTest.o Graph.o List.o
		$(CC) -o GraphTest GraphTest.o Graph.o List.o -g

FindPath.o	:	FindPath.c
		$(CC) -c FindPath.c

GraphTest.o	:	GraphTest.c
		$(CC) -c GraphTest.c

Graph.o		:	Graph.c List.c
		$(CC) -c Graph.c List.c

List.o		:	List.c
		$(CC) -c List.c

clean		:
		rm -rf *.o FindPath GraphTest infer-out

format		:
		clang-format -i -style=file *.c *.h

valgrind	:
		$(MEMCHECK) FindPath

infer		:
		make clean; infer-capture -- make; infer-analyze -- make 
