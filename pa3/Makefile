CFLAGS = -Wall -std=c11;
CC = clang $(CFLAGS)

all		:	FindPath

FindPath	:	FindPath.o Graph.o List.o
		$(CC) -o FindPath FindPath.o Graph.o List.o -g

FindPath.o	:	FindPath.c
		$(CC) -c FindPath.c

Graph.o		:	Graph.c
		$(CC) -c Graph.c

List.o		:	List.c
		(CC) -c List.c

clean		:
		rm -rf *.o FindPath infer-out

format		:
		clang-format -i -style=file *.c *.h
