#-------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA4
# README.md
#--------------------------------------

#Program

FindComponents.c - This is an executable file that uses the Graph ADT to performDepth First Search. This program will take in vertices and create a graph, and then finds the strong connected components and prints it out. A infile and an outfile must be given in order to run.

Graph.c - This is the Graph ADT. It's purpose is to create a graph and store information as well as performing the DFS.

Graph.h - The header file for Graph.c

List.c- This is the List ADT. Stores data in a doubly linked list.

List.h - This is the header file for List ADT.

GraphTest.c - Test client for Graph.c

#MAKEFILE

Type make or make all to build FindComponents

Type make GraphTest to build Graph test client

Type make clean to remove .o files

Type make infer to check for errors

Type make valgrind to check for memory leak.
