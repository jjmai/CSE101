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
  int length;
} GraphObj;

Graph newGraph(int n) {
  Graph g = malloc(sizeof(GraphObj));
  g->list = calloc(n + 1, sizeof(List));
  g->color = calloc(n + 1, sizeof(GraphObj));
  g->distance = calloc(n + 1, sizeof(GraphObj));
  g->parent = calloc(n + 1, sizeof(GraphObj));
  g->source = 0;
  g->size = 0;
  g->order = 0;
  g->length = n;
  return g;
}

void freeGraph(Graph *pG) {
  if (pG != NIL && *pG != NIL) {
    for (int i = 0; i <= (*pG)->length; i++) {
      if (length((*pG)->list[i]) > 0) {
        freeList(&(*pG)->list[i]);
      }
    }
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
  if(getSource(G)!=NIL) {
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
  for (int i = 0; i <= G->length; i++) {
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
  if (length(G->list[u]) == -1) {
    G->list[u] = newList();
    append(G->list[u], v);
    // G->size++;
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
    // G->size++;
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
    G->order++;
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
    //  G->size++;
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
    G->order++;
  }
  G->size++;
}

void BFS(Graph G, int s) {
  if (G == NULL) {
    printf("ERROR on BFS");
    exit(1);
  }
  for (int i = 0; i <= G->length; i++) {
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

void printGraph(FILE *out, Graph G) {
  for (int i = 1; i <= G->length; i++) {
    fprintf(out, "%d: ", i);
    if (length(G->list[i]) > 0) {
      printList(out, G->list[i]);
    }
    fprintf(out, "\n");
  }
}
