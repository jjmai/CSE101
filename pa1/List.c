#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeObj {
  int data;
  struct NodeObj *next;
  struct NodeObj *prev;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
  Node front;
  Node back;
  int length;
  int index;
} ListObj;

Node cursor = NULL;

Node newNode(int data) {
  Node n = malloc(sizeof(NodeObj));
  n->data = data;
  n->next = NULL;
  n->prev = NULL;

  return n;
}

void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

List newList(void) {
  List l = malloc(sizeof(ListObj));
  l->front = l->back = NULL;
  l->length = 0;
  l->index = -1;

  return l;
}

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
  }
  free(*pL);
  *pL = NULL;
}

int length(List L) { return L->length; }

int index(List L) {
  if (cursor != NULL) {
    return L->index;
  }
  return -1;
}

int front(List L) {
  if (L->length > 0) {
    return L->front->data;
  } else {
    return 0;
  }
}

int back(List L) {
  if (L->length > 0) {
    return L->back->data;
  }
  return 0;
}


int get(List L) {
    if(L->length>0 && L->index >=0) {
        return cursor->data;
    } else {
        return 0;
    }
}

void clear(List L) {
  Node n = L->front;
  while (n != NULL) {
    cursor = n;
    delete (L);
    n = n->next;
  }
  L->length = 0;
  L->index = -1;
}

void moveFront(List L) {
  if (L != NULL) {
    cursor = L->front;
    L->index = 0;
  }
}

void moveBack(List L) {
  if (L != NULL) {
    cursor = L->back;
    L->index = L->length - 1;
  }
}

void movePrev(List L) {
  if (cursor != NULL && cursor != L->front) {
    cursor = cursor->prev;
  } else if (cursor != NULL && cursor == L->front) {
    cursor = L->front->prev;
  }
  L->index--;
}

void moveNext(List L) {
  if (cursor != NULL && cursor != L->back) {
    cursor = cursor->next;
  } else if (cursor != NULL && cursor == L->back) {
    cursor = L->back->next;
  }
  L->index++;
}

void prepend(List L, int data) {
  Node n = newNode(data);
  if (L == NULL) {
    printf("ERROR");
    exit(1);
  }
  if (L->length == 0) {
    L->back = n;
  } else {
    L->front->prev = n;
  }
  n->next = L->front;
  L->front = n;

  L->length++;
}

void append(List L, int data) {
  Node n = newNode(data);
  if (L == NULL) {
    printf("ERROR");
    exit(1);
  }
  if (L->length == 0) {
    L->front = n;
  } else {
    L->back->next = n;
    n->prev = L->back;
  }
  L->back = n;
  L->length++;
}

void insertBefore(List L, int data) {
  if (L->length > 0 && cursor != NULL) {

    Node temp = L->front;
    while (temp != cursor) {
      temp = temp->next;
    }
    Node n = newNode(data);

    if (temp == L->front) {
      n->prev = NULL;
      L->front = n;
    } else {
      n->prev = temp->prev;
      temp->prev->next = n;
    }
    n->next = temp;
    temp->prev = n;

    L->length++;
  }
}

void insertAfter(List L, int data) {
  if (L->length > 0 && cursor != NULL) {
    Node temp = L->front;
    while (temp != cursor) {
      temp = temp->next;
    }
    Node n = newNode(data);

    if (temp == L->back) {
      n->next = NULL;
      L->back = n;
    } else {
      n->next = temp->next;
      temp->next->prev = n;
    }
    n->prev = temp;
    temp->next = n;
    L->length++;
  }
}

void deleteFront(List L) {
  if (L->length > 0) {
    Node temp = L->front;
    L->front = L->front->next;
    temp->next->prev = temp->prev;
    L->length--;
    freeNode(&temp);
  }
}

void deleteBack(List L) {
  if (L->length > 0) {
    Node temp = L->back;
    L->back = L->back->prev;
    temp->prev->next = temp->next;
    L->length--;
    freeNode(&temp);
  }
}

void delete (List L) {
  if (L->length > 0 && cursor != NULL && L->index >= 0) {
    Node temp = L->front;
    while (temp != cursor) {
      temp = temp->next;
    }
    if (temp == L->front) {
      L->front = L->front->next;
    } else {
      temp->prev->next = temp->next;
    }
    if (temp == L->back) {
      L->back = temp->prev;
    } else {
      temp->next->prev = temp->prev;
    }
    cursor = NULL;
    L->length--;
    freeNode(&temp);
  }
}

void print_list(List L) {
  Node n = NULL;

  for (n = L->front; n != NULL; n = n->next) {
    printf("%d .", n->data);
  }
  printf("\n");
}
