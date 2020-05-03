/*********************************************
 * Jordan Mai, jmai12
 * 2020 Spring CSE101,PA4
 * Graph.h
 * Header File for Graph.c
 **********************************************/

#include "List.h"
#ifndef _GRAPH_H
#define _GRAPH_H

#ifndef NIL
#define NIL 0
#endif
#define INF -1
#define UNDEF -2

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph *pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
void printGraph(FILE *out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif
