#include "Graph.h"
#include "List.h"
#define EMPTY -1

typedef struct GraphObj {
  List *list;
  int *color;
  int *distance;
  int *parent;
  int order;
  int size;
  int source;
} GraphObj;

Graph newGraph(int n) {
  Graph g = malloc(sizeof(GraphObj));
  // linked list for neighbors
  g->list = calloc(n + 1, sizeof(List));
  // b,w,g
  g->color = calloc(n + 1, sizeof(GraphObj));
  g->distance = calloc(n + 1, sizeof(GraphObj));
  // contain predecessor
  g->parent = calloc(n + 1, sizeof(GraphObj));
  g->source = 0;
  g->size = n;
  g->order = 0;
  return g;
}
void freeGraph(Graph *pG) {
  if (pG != NIL && *pG != NIL) {
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
  return G->distance[u];
}

void getPath(List L, Graph G, int u) {
  if (getSource(G) == NIL) {
    printf("ERROR on getPath() .no source found");
    exit(1);
  }
  if (getSource(G) == u) {
    append(L, u);
  } else if (G->parent[u] == NIL) {
    // clear(L);
    append(L, NIL);
    // fprintf("The distance from %d to %d is infinity\n", getSource(G), u);
  } else {
    getPath(L, G, getParent(G, u));
    append(L, u);
  }
}

void addEdge(Graph G, int u, int v) {
  if (G == NIL) {
    printf("ERROR on addEDGE()");
    exit(1);
  }
  if (length(G->list[u]) == -1) {
    G->list[u] = newList();
    append(G->list[u], v);
  } else {
    append(G->list[u], v);
  }
  if (length(G->list[v]) == -1) {
    G->list[v] = newList();
    append(G->list[v], u);
  } else {
    append(G->list[v], u);
  }
  G->order++;
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
    prepend(G->list[u], v);
  }
  G->order++;
}

void BFS(Graph G, int s) {
  if (length(G->list[s]) == EMPTY) {
    printf("ERROR, %d doesn't exist", s);
    exit(1);
  }
  for (int i = 0; i <= getSize(G); i++) {
    if (length(G->list[i]) > 0) {
      G->color[i] = 'w';
      G->distance[i] = INF;
      G->parent[i] = NIL;
    }
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

void printGraph(FILE *out, Graph G) {
  for (int i = 1; i <= G->size; i++) {
    if (length(G->list[i]) > 0) {
      fprintf(out, "%d: ", i);
      printList(out, G->list[i]);
      fprintf(out, "\n");
    }
  }
}
