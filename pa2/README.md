#----------------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA2
# README.md
#-----------------------------------------------------

#PROGRAM

Arithmetic.c - This is a executable file that is able to add,subtract,multiply any number. To run this program, the user must include a infile containing numbers and a outfile. This program will ead in to numbersand perform arithmetic and will write the answers to the outfile.

BigInteger.c - This is a BigInteger ADT. It's purpose is to do all the operations that Arithmetic.c calls

BigInteger.h - This is a header file for BigInteger.c

BigIntegerTest.c - This is a test file for BigInteger ADT.

List.c - This contains the List ADT that stores all the numbers in BigInteger ADT

List.h - Header file for List ADT

ListClientTest.c - test file for List ADT

#MAKEFILE

Type make or make all to build Arithmetic.
Type make ListClient to build ListClient
Type make BigIntegerTest to build BigIntegerClient.
Type make clean to remove .o files
Type make infer to check for errors
Type make valgrind to check for memory leaks

