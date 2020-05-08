CFLAGS = -Wall -std=c11
CC = clang $(CFLAGS)

all		:	Lex

Lex		:	Lex.o Dictionary.o 
		$(CC) -o Lex Lex.o Dictionary.o -g

Lex.o		:	Lex.c
		$(CC) -c Lex.c

Dictionary.o	:	Dictionary.c
		$(CC) -c Dictionary.c

clean		:
		rm -rf *.o Lex infer-out

format		:
		clang-format -i -style=file *.c *.h
