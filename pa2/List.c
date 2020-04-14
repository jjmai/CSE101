/**************************
 *  * Jordan Mai,jmai12
 *   * 2020 Spring CSE101 PA1
 *    * List.c
 *     * List ADT
 *      **************************/

#include "List.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeObj {
  long data;
  struct NodeObj *next;
  struct NodeObj *prev;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  long length;
  long index;
} ListObj;

Node newNode(long data) {
  Node n = malloc(sizeof(NodeObj));
  assert(n);
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
  assert(l);
  l->front = l->back = NULL;
  l->length = 0;
  l->index = -1;
  l->cursor = NULL;
  return l;
}

long isEmpty(List pL) {
  if (pL == NULL) {
    printf("ERROR: calling isEmpty()");
    exit(1);
  }
  return (pL->length == 0);
}

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    while (!isEmpty(*pL)) {
      moveFront(*pL);
      delete (*pL);
    }
  }
  free(*pL);
  *pL = NULL;
}

long length(List L) {
  if (L) {
    return L->length;
  } else {
    return -1;
  }
}

long l_index(List L) {
  if (L->cursor != NULL) {
    Node temp = L->front;
    L->index = 0;
    while (temp != L->cursor) {
      L->index++;
      temp = temp->next;
    }
    return L->index;
  }
  return -1;
}

long front(List L) {
  if (L->length > 0) {
    return L->front->data;
  } else {
    return 0;
  }
}
long back(List L) {
  if (L->length > 0) {
    return L->back->data;
  }
  return 0;
}

long get(List L) {
  if (L->length > 0 && L->index >= 0) {
    return L->cursor->data;
  } else {
    return -1;
  }
}

long l_equals(List A, List B) {
  if (length(A) != length(B)) {
    return 0;
  }
  Node temp1 = A->front;
  Node temp2 = B->front;
  while (temp1 != NULL && temp2 != NULL) {
    if (temp1->data != temp2->data) {
      return 0;
    }
    temp1 = temp1->next;
    temp2 = temp2->next;
  }
  return 1;
}

void clear(List L) {
  Node temp = L->front;
  while (temp != NULL) {
    delete (L);
    temp = temp->next;
  }
  L->length = 0;
  L->index = -1;
}
void moveFront(List L) {
  if (L != NULL) {
    L->cursor = L->front;
    L->index = l_index(L);
  }
}

void moveBack(List L) {
  if (L != NULL) {
    L->cursor = L->back;
    L->index = l_index(L);
  }
}

void movePrev(List L) {
  if (L->cursor != NULL && L->cursor != L->front) {
    L->cursor = L->cursor->prev;
    L->index = l_index(L);
  } else if (L->cursor != NULL && L->cursor == L->front) {
    L->cursor = L->front->prev;
    L->index = l_index(L);
  }
}

void moveNext(List L) {
  if (L->cursor != NULL && L->cursor != L->back) {
    L->cursor = L->cursor->next;
    L->index = l_index(L);
  } else if (L->cursor != NULL && L->cursor == L->back) {
    L->cursor = L->back->next;
    L->index = l_index(L);
  }
}

void prepend(List L, long data) {
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

void append(List L, long data) {
  Node n = newNode(data);
  if (L == NULL) {
    printf("ERROR");
    exit(1);
  }
  if (L->length == 0) {
    L->front = n;
  } else {
    L->back->next = n;
  }
  n->prev = L->back;
  L->back = n;
  L->length++;
}

void insertBefore(List L, long data) {
  if (L->length > 0 && L->cursor != NULL && L->index != -1) {

    Node temp = L->front;
    while (temp != L->cursor) {
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

void insertAfter(List L, long data) {
  if (L->length > 0 && L->cursor != NULL && L->index != -1) {
    Node temp = L->front;
    while (temp != L->cursor) {
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
    if (L->length != 1) {
      L->front = L->front->next;
      temp->next->prev = temp->prev;
    }
    if (L->cursor == temp) {
      L->cursor = NULL;
      L->index = -1;
    }
    L->length--;
    freeNode(&temp);
  }
}

void deleteBack(List L) {
  if (L->length > 0) {
    Node temp = L->back;
    if (L->length != 1) {
      temp->prev->next = temp->next;
      L->back = temp->prev;
    }
    if (L->cursor == temp) {
      L->cursor = NULL;
      L->index = -1;
    }
    L->length--;
    freeNode(&temp);
  }
}

void delete (List L) {
  if (L->length > 0 && L->cursor != NULL && L->index >= 0) {
    Node temp = L->front;
    while (temp != L->cursor) {
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
    L->cursor = NULL;
    L->length--;
    freeNode(&temp);
  }
}

List copyList(List L) {
  List LL = newList();
  Node temp = L->front;
  while (temp != NULL) {
    append(LL, temp->data);
    temp = temp->next;
  }
  return LL;
}

void printList(FILE *out, List L) {
  Node n = NULL;
  char array[length(L)];

  for (n = L->front; n != NULL; n = n->next) {
    sprintf(array, "%d ", n->data);
    fputs(array, out);
  }
}

void set(List L, long x) {
  if (L->length > 0 && L->index >= 0) {

    L->cursor->data = x;
  }
}
