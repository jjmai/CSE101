#------------------------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring 2020, PA7
#
# Makefile for List ADT
#
# make			makes Shuffle.cpp
# make ListTest	makes ListClient test
# make clean		remove all binaries
# make infer		check for errors
# make format		auto formats all *.c *.h
# make valgrind		checks for memory leaks
#-------------------------------------------------------------------

COMPILE	= g++ -std=c++11 -Wall -c
LINK = g++ -std=c++11 -Wall -o
MEMCHECK = valgrind --leak-check=full

all		:	Shuffle 

Shuffle		:	Shuffle.o List.o
		$(LINK) Shuffle Shuffle.o List.o -g

ListTest	:	ListTest.o List.o
		$(LINK) ListTest ListTest.o List.o -g

Shuffle.o	:	Shuffle.cpp 
		$(COMPILE) -cpp Shuffle.cpp

ListTest.o	:	ListTest.cpp
		$(COMPILE) -cpp ListTest.cpp

List.o		:	List.cpp
		$(COMPILE) -cpp List.cpp 

clean		:
		rm -rf *.o Shuffle ListTest infer-out

format		:
		clang-format -i -style=file *.cpp *.h

infer		:
		make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
		MEMCHECK Shuffle 100
