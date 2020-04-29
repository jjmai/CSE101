/**************************
 * * Jordan Mai,jmai12
 * * 2020 Spring CSE101 PA3
 * * Graph.c
 * * Graph ADT
 ****************************/

#include "Graph.h"
#include "List.h"
#include <assert.h>
#define EMPTY -1
void visit(Graph G, int u, int *time);

typedef struct GraphObj {
  List *list;    // array of List
  int *color;    // b , g , w
  int *distance; // array of distance from source
  int *parent;   // array of predecessors
  int order;     // max possible number nodes
  int size;      // graph edges
  int source;    // cursor of graph
  int *discover;
  int *finish;
} GraphObj;

Graph newGraph(int n) {
  Graph g = malloc(sizeof(GraphObj));
  assert(g);
  g->list = calloc(n + 1, sizeof(List));
  g->color = calloc(n + 1, sizeof(GraphObj));
  g->distance = calloc(n + 1, sizeof(GraphObj));
  g->parent = calloc(n + 1, sizeof(GraphObj));
  g->source = 0;
  g->size = 0;
  g->order = n;
  g->discover = calloc(n + 1, sizeof(GraphObj));
  g->finish = calloc(n + 1, sizeof(GraphObj));

  return g;
}

void freeGraph(Graph *pG) {
  if (pG != NIL && *pG != NIL) {
    for (int i = 0; i <= getOrder(*pG); i++) {
      if (length((*pG)->list[i]) > 0) {
        freeList(&(*pG)->list[i]);
      }
    }
    free((*pG)->list);
    free((*pG)->color);
    free((*pG)->distance);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
  }
}

int getOrder(Graph G) {
  if (G == NULL) {
    printf("ERROR on getSize");
    exit(1);
  }
  return G->order;
}

int getSize(Graph G) {
  if (G == NULL) {
    printf("ERROR on getSize");
    exit(1);
  }
  return G->size;
}

int getSource(Graph G) {
  if (G == NULL) {
    printf("ERROR on GetSource()");
    exit(1);
  }
  if (G->source != 0) {
    return G->source;
  }
  return NIL;
}

int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("ERROR on getParent()");
    exit(1);
  }
  return G->parent[u];
}

int getDist(Graph G, int u) {
  if (G == NULL) {
    printf("ERROR on getDist");
    exit(1);
  }
  if (getSource(G) != NIL) {
    return G->distance[u];
  }
  return INF;
}

void getPath(List L, Graph G, int u) {
  if (getSource(G) == NIL) {
    printf("ERROR on getPath() .no source found");
    exit(1);
  }
  if (getSource(G) == u) {
    append(L, u);
  } else if (G->parent[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, getParent(G, u));
    append(L, u);
  }
}

void makeNull(Graph G) {
  if (G == NULL) {
    printf("ERROR on makeNULL");
    exit(1);
  }
  G->source = 0;
  G->size = 0;
  G->order = 0;
  for (int i = 0; i <= getOrder(G); i++) {
    if (length(G->list[i]) > 0) {
      G->color[i] = '\0';
      G->distance[i] = '\0';
      G->parent[i] = '\0';
      moveFront(G->list[i]);
      while (get(G->list[i]) != EMPTY) {
        delete (G->list[i]);
        moveFront(G->list[i]);
      }
    }
  }
}

void addEdge(Graph G, int u, int v) {
  if (G == NIL) {
    printf("ERROR on addEDGE()");
    exit(1);
  }
  // if first index, then create a list at index
  if (length(G->list[u]) == -1) {
    G->list[u] = newList();
    append(G->list[u], v);
  } else {
    moveFront(G->list[u]);
    while (v > get(G->list[u]) && get(G->list[u]) != EMPTY) {
      moveNext(G->list[u]);
    }
    if (index(G->list[u]) == EMPTY) {
      append(G->list[u], v);
    } else {
      insertBefore(G->list[u], v);
    }
  }

  if (length(G->list[v]) == -1) {
    G->list[v] = newList();
    append(G->list[v], u);
  } else {
    moveFront(G->list[v]);
    while (u > get(G->list[v]) && get(G->list[v]) != EMPTY) {
      moveNext(G->list[v]);
    }
    if (index(G->list[v]) == EMPTY) {
      append(G->list[v], u);
    } else {
      insertBefore(G->list[v], u);
    }
  }
  G->size++;
}

void addArc(Graph G, int u, int v) {
  if (G == NIL) {
    printf("ERROR on addArc()");
    exit(1);
  }
  if (length(G->list[u]) == -1) {
    G->list[u] = newList();
    prepend(G->list[u], v);
  } else {
    moveFront(G->list[u]);
    while (v > get(G->list[u]) && get(G->list[u]) != EMPTY) {
      moveNext(G->list[u]);
    }
    if (index(G->list[u]) == EMPTY) {
      append(G->list[u], v);
    } else {
      insertBefore(G->list[u], v);
    }
  }
  G->size++;
}

void BFS(Graph G, int s) {
  if (G == NULL) {
    printf("ERROR on BFS");
    exit(1);
  }
  for (int i = 0; i <= getOrder(G); i++) {
    G->color[i] = 'w';
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  G->parent[s] = NIL;
  G->color[s] = 'g';
  G->distance[s] = 0;
  G->source = s;

  List l = newList();
  prepend(l, s);
  while (length(l) > 0) {
    int num = front(l);
    deleteFront(l);
    moveFront(G->list[num]);
    if (G->list[s] == NULL) {
      break;
    }
    while (get(G->list[num]) != EMPTY) {
      if (G->color[get(G->list[num])] == 'w') {
        G->color[get(G->list[num])] = 'g';
        G->distance[get(G->list[num])] = G->distance[num] + 1;
        G->parent[get(G->list[num])] = num;
        append(l, get(G->list[num]));
      }
      moveNext(G->list[num]);
    }
    G->color[num] = 'b';
  }
  freeList(&l);
}

int getDiscover(Graph G, int u) {
  if (G == NULL) {
    printf("ERROR on getDiscover()");
    exit(1);
  }
  return G->discover[u];
}

int getFinish(Graph G, int u) {
  if (G == NULL) {
    printf("ERROR on getFinish");
    exit(1);
  }
  return G->finish[u];
}

void DFS(Graph G, List S) {
  if (G == NULL) {
    printf("ERROR on DFS");
    exit(1);
  }
  if (length(S) != getOrder(G)) {
    printf("error on DFSlength");
    exit(1);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = 'w';
    G->parent[i] = NIL;
  }
  int time = 0, counter = 0;
  moveFront(S);
  while (get(S) != EMPTY) {
    if (G->color[get(S)] == 'w') {
      visit(G, get(S), &time, S);
    }
    moveNext(S);
  }
  for (int i = 0; i < getOrder(G); i++) {
    moveBack(S);
    deleteBack(S);
  }
}

void visit(Graph G, int u, int *time, List S) {
  *time = *time + 1;
  G->discover[u] = *time;
  G->color[u] = 'g';

  if (G->list[u] != NULL) {
    moveFront(G->list[u]);
    while (get(G->list[u]) != EMPTY) {
      if (G->color[get(G->list[u])] == 'w') {
        G->parent[get(G->list[u])] = u;
        visit(G, get(G->list[u]), time, S);
      }
      moveNext(G->list[u]);
    }
  }
  G->color[u] = 'b';
  *time = *time + 1;
  G->finish[u] = *time;
  prepend(S, u);
}
void printGraph(FILE *out, Graph G) {
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i);
    if (length(G->list[i]) > 0) {
      printList(out, G->list[i]);
    }
    fprintf(out, "\n");
  }
}

Graph copyGraph(Graph G) {
  if (G == NULL) {
    printf("error on copygraph");
    exit(1);
  }
  Graph gg = newGraph(getOrder(G));

  for (int i = 1; i <= getOrder(G); i++) {
    if (G->list[i] != NULL) {
      moveFront(G->list[i]);
      while (get(G->list[i]) != EMPTY) {
        addArc(gg, i, get(G->list[i]));
        moveNext(G->list[i]);
      }
    }
  }
  return gg;
}

Graph transpose(Graph G) {
  Graph gg = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    if (G->list[i] != NULL) {
      moveFront(G->list[i]);
      while (get(G->list[i]) != EMPTY) {
        addArc(gg, get(G->list[i]), i);
        moveNext(G->list[i]);
      }
    }
  }
  return gg;
}
