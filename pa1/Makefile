CFLAGS =-Wpedantic -Wall -Werror -std=c99
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
		rm -rf *.o Lex infer-out

format		:
		clang-format -i -style=file *.c *.h
