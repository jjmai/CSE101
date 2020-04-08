#----------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA1
# README.md
#-----------------------------------------------------

#PROGRAM

Lex.c - This is a executable file that consists of the main function where the program runs. This program will use List.c in order to function. To run this program, user must insert an infile and an outfile respectively in command line. The program then takes in strings line by line in infile and sorts them alphabetially by ascii value inside a LIST. The output is printed in the outfile.

List.c - This is a LIST ADT, which is used by Lex.c to store data. It stores index of an array that consists of strings.

List.h - This is the header file for List.c.

ListClient.c - A test for List.c

#MAKEFILE

Type make or make all to build Lex.
Type make ListClient to build ListClient
Type make clean to remove .o files
Type make infer to check for errors
Type make valgrind to check for memory leaks
