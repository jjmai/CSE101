#------------------------------------------
# Jordan Mai, jmai12
# CSE101 Spring, PA2
# README.md
#-------------------------------------------

#Program

FindPath.c - This is an executable file that uses the Graph ADT to function. This program will create a path graph that takes in edges and will print out the shortest paths from one edge to another based on file input. A requirement is that the user must include a infile and an outfile.

Graph.c - This is the Graph ADT. It's purpose is to store inputs in array of lists and create a graph. It also has the function to search for elements and find shortest paths.

Graph.h - Header file for Graph.c

List.c - This is the List ADT. It's purpose is to store numbers in a double linked list.

List.h - Header file for List.c

GraphTest.c - Test client for Graph.c

#MAKEFILE

Type make or make all to build FindPath.

Type make GraphTest to build Graphest.

Type make clean to remove.o files

Type make infer to check for errors

Type make valgrind to run mememory check for FindPath
