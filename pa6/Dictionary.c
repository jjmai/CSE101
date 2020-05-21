#include "Dictionary.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeObj {
  KEY_TYPE key;
  VAL_TYPE value;
  char color;
  struct NodeObj *left;
  struct NodeObj *right;
  struct NodeObj *parent;
} NodeObj;

typedef NodeObj *Node;

void pre(FILE *out, Dictionary D, Node z);
void post(FILE *out, Dictionary D, Node z);
void rbTransplant(Dictionary D, Node x, Node y);
void rbInsertFixUp(Dictionary D, Node z);
void rbDeleteFixUp(Dictionary D, Node x);
void leftRotate(Dictionary D, Node x);
void rightRotate(Dictionary D, Node x);
void rbInsert(Dictionary D, KEY_TYPE z, VAL_TYPE v);
void rbDelete(Dictionary D, Node z);

typedef struct DictionaryObj {
  Node root;
  int unique;
  int size;
  Node cursor; // for move functions
  Node nil;
} DictionaryObj;

Node newNode(char *k, int *v) {
  Node n = malloc(sizeof(NodeObj));
  assert(n);
  n->key = k;
  n->value = v;
  n->color = 'b';
  n->left = NULL;
  n->right = NULL;
  n->parent = NULL;
  return n;
}

void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// void deleteAll(Dictionary D, Node R) {
// if (R != D->nil) {
// deleteAll(D, R->left);
// deleteAll(D, R->right);
// freeNode(&R);
// }
//}

Dictionary newDictionary(int unique) {
  Dictionary d = malloc(sizeof(struct DictionaryObj));
  assert(d);
  d->size = 0;
  d->nil = newNode(KEY_UNDEF, VAL_UNDEF);
  d->root = d->nil;
  d->cursor = d->nil;
  if (unique == 0) {
    d->unique = 0;
  } else {
    d->unique = 1;
  }
  return d;
}

void freeDictionary(Dictionary *pD) {
  if (pD != NULL && *pD != NULL) {
    makeEmpty(*(pD));
    free(*pD);
    *pD = NULL;
  }
}

int size(Dictionary D) {
  if (D == NULL) {
    printf("ERROR on size");
    exit(1);
  }
  return D->size;
}

int getUnique(Dictionary D) {
  if (D == NULL) {
    printf("ERROR get UNIQU");
    exit(1);
  }
  if (D->unique == 1) {
    return 1;
  } else {
    return 0;
  }
}
Node findKey(Dictionary D, Node n, KEY_TYPE k) {
  if (n == D->nil || KEY_CMP(k, n->key) == 0) {
    return n;
  }
  if (strcmp(k, n->key) < 0) {
    return findKey(D, n->left, k);
  } else {
    return findKey(D, n->right, k);
  }
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
  if (D == NULL) {
    printf("ERROR on lookup");
    exit(1);
  }
  if (size(D) > 0) {
    Node n = D->nil;
    n = findKey(D, D->root, k);
    if (n != D->nil) {
      return n->value;
    }
  }
  return VAL_UNDEF;
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
  if (D == NULL) {
    printf("ERROR on insert");
    exit(1);
  }
  rbInsert(D, k, v);
  // D->size++;
}

void delete (Dictionary D, KEY_TYPE k) {
  if (D == NULL) {
    printf("ERROR on delete");
    exit(1);
  }

  Node temp = D->nil;
  temp = findKey(D, D->root, k);
  rbDelete(D, temp);
  D->size--;
}

void makeEmpty(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr, "ERROR on makeEmpty");
    exit(1);
  }
  // deleteAll(D, D->root);
  D->root = D->nil;
  D->size = 0;
  D->cursor = D->nil;
}

VAL_TYPE beginForward(Dictionary D) {
  if (D == NULL) {
    printf("error on beginforward");
    exit(1);
  }
  if (size(D) > 0) {
    Node A = D->root;
    while (A->left != D->nil) {
      A = A->left;
    }
    D->cursor = A;
    return A->value;
  }
  return VAL_UNDEF;
}
VAL_TYPE beginReverse(Dictionary D) {
  if (D == NULL) {
    printf("error on beginReverse");
    exit(1);
  }
  if (size(D) > 0) {
    Node A = D->root;
    while (A->right != D->nil) {
      A = A->right;
    }
    D->cursor = A;
    return A->value;
  }
  return VAL_UNDEF;
}

KEY_TYPE currentKey(Dictionary D) {
  if (D == NULL) {
    printf("ERROR ON currentKEY");
    exit(1);
  }
  if (D->cursor != D->nil) {
    return D->cursor->key;
  }
  return KEY_UNDEF;
}

VAL_TYPE currentVal(Dictionary D) {
  if (D == NULL) {
    printf("ERROR ON currentKEY");
    exit(1);
  }
  if (D->cursor != D->nil) {
    return D->cursor->value;
  }
  return VAL_UNDEF;
}

VAL_TYPE next(Dictionary D) {
  if (D == NULL) {
    printf("ERROR on next");
    exit(1);
  }
  if (D->cursor == D->nil) {
    return VAL_UNDEF;
  }
  Node A = D->cursor;
  if (A->right != D->nil) {
    Node current = A->right;
    while (current->left != D->nil) {
      current = current->left;
    }
    D->cursor = current;
    return current->value;
  }
  Node temp = A->parent;
  while (temp != D->nil && A == temp->right) {
    A = temp;
    temp = temp->parent;
  }
  if (temp == D->nil) {
    D->cursor = D->nil;
    return VAL_UNDEF;
  }
  D->cursor = temp;
  return temp->value;
}

VAL_TYPE prev(Dictionary D) {
  if (D == NULL) {
    fprintf(stderr, "ERROR on prev");
    exit(1);
  }
  if (D->cursor == D->nil) {
    return VAL_UNDEF;
  }
  Node A = D->cursor;
  if (A->left != D->nil) {
    Node current = A->left;
    while (current->right != D->nil) {
      current = current->right;
    }
    D->cursor = current;
    return current->value;
  }
  Node temp = A->parent;
  while (temp != D->nil && A == temp->left) {
    A = temp;
    temp = temp->parent;
  }
  if (temp == D->nil) {
    D->cursor = temp;
    return VAL_UNDEF;
  }
  D->cursor = temp;
  return temp->value;
}

void printDictionary(FILE *out, Dictionary D, const char *ord) {
  if (KEY_CMP(ord, "pre") == 0) {
    pre(out, D, D->root);
  } else if (KEY_CMP(ord, "in") == 0) {
    beginForward(D);
    for (int i = 0; i < size(D); i++) {
      fprintf(out, "%s", currentKey(D));
      next(D);
    }
  } else if (KEY_CMP(ord, "post") == 0) {
    post(out, D, D->root);
  }
}
void pre(FILE *out, Dictionary D, Node z) {
  if (z == D->nil) {
    return;
  }
  fprintf(out, "%s", z->key);
  pre(out, D, z->left);
  pre(out, D, z->right);
}
void post(FILE *out, Dictionary D, Node z) {
  if (z == D->nil) {
    return;
  }
  post(out, D, z->left);
  post(out, D, z->right);
  fprintf(out, "%s", z->key);
}

void leftRotate(Dictionary D, Node x) {
  if (D == NULL) {
    printf("ERROR on leftrotate");
    exit(1);
  }
  Node A = x;
  Node y;

  y = A->right;
  A->right = y->left;
  if (y->left != D->nil) {
    y->left->parent = A;
  }
  y->parent = A->parent;
  if (A->parent == D->nil) {
    D->root = y;
  } else if (A == A->parent->left) {
    A->parent->left = y;
  } else {
    A->parent->right = y;
  }
  y->left = A;
  A->parent = y;
}

void rightRotate(Dictionary D, Node x) {
  if (D == NULL) {
    printf("ERROR on right rotate");
    exit(1);
  }
  Node A = x;
  Node y = D->nil;

  y = A->left;
  A->left = y->right;
  if (y->right != D->nil) {
    y->right->parent = A;
  }
  y->parent = A->parent;
  if (A->parent == D->nil) {
    D->root = y;
  } else if (A == A->parent->right) {
    A->parent->right = y;
  } else {
    A->parent->left = y;
  }
  y->right = A;
  A->parent = y;
}

void rbInsert(Dictionary D, KEY_TYPE z, VAL_TYPE v) {
  if (D == NULL) {
    printf("ERROR on rbinsert");
    exit(1);
  }
  bool check = false;
  if (getUnique(D) == 1) {
    if (lookup(D, z) != VAL_UNDEF) {
      check = true;
    }
  }
  if (getUnique(D) == 0 || check == false) {
    Node y = D->nil;
    Node A = D->root;
    Node new = newNode(z, v);
    while (A != D->nil) {
      y = A;
      if (KEY_CMP(z, A->key) < 0) {
        A = A->left;
      } else if (KEY_CMP(z, A->key) >= 0) {
        A = A->right;
      }
    }
    new->parent = y;
    if (y == D->nil) {
      new->color = 'b';
      D->root = new;
    } else if (KEY_CMP(new->key, y->key) < 0) {
      y->left = new;
    } else {
      y->right = new;
    }
    new->left = D->nil;
    new->right = D->nil;
    new->color = 'r';
    rbInsertFixUp(D, new);
    D->size++;
  }
}
void rbInsertFixUp(Dictionary D, Node z) {
  if (D == NULL) {
    printf("ERROR on rbinsertfixup");
    exit(1);
  }
  Node A = z;
  Node y = D->nil;

  while (A->parent != D->nil && A->parent->color == 'r') {
    if (A->parent == A->parent->parent->left) {
      y = A->parent->parent->right;
      if (y != D->nil && y->color == 'r') {
        A->parent->color = 'b';
        y->color = 'b';
        A->parent->parent->color = 'r';
        A = A->parent->parent;
      } else {
        if (A == A->parent->right) {
          A = A->parent;
          leftRotate(D, A);
        }
        A->parent->color = 'b';
        A->parent->parent->color = 'r';
        rightRotate(D, A->parent->parent);
      }
    } else {
      y = A->parent->parent->left;
      if (y != D->nil && y->color == 'r') {
        A->parent->color = 'b';
        y->color = 'b';
        A->parent->parent->color = 'r';
        A = A->parent->parent;
      } else {
        if (A == A->parent->left) {
          A = A->parent;
          rightRotate(D, A);
        }
        A->parent->color = 'b';
        A->parent->parent->color = 'r';
        leftRotate(D, A->parent->parent);
      }
    }
  }
  D->root->color = 'b';
}

void rbTransplant(Dictionary D, Node x, Node y) {
  if (D == NULL) {
    printf("ERROR on rbTransplant");
    exit(1);
  }
  if (x->parent == D->nil) {
    D->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->parent = x->parent;
}

void rbDelete(Dictionary D, Node z) {
  if (D == NULL) {
    printf("error on rb Delete");
    exit(1);
  }
  if (D->cursor != D->nil) {
    if (D->cursor == z) {
      D->cursor = D->nil;
    }
  }

  Node A = z;
  Node y = D->nil;
  Node x = D->nil;

  y = A;
  char o_color = y->color;
  if (A->left == D->nil) {
    x = A->right;
    rbTransplant(D, A, A->left);
  } else if (A->right == D->nil) {
    x = A->left;
    rbTransplant(D, A, A->left);
  } else {
    y = A->right;
    while (y->left != D->nil) {
      y = y->left;
    }
    x = y->right;
    o_color = y->color;
    if (y->parent == A) {
      x->parent = y;
    } else {
      rbTransplant(D, y, y->right);
      y->right = A->right;
      y->right->parent = y;
    }
    rbTransplant(D, A, y);
    y->left = A->left;
    y->left->parent = y;
    y->color = A->color;
  }
  if (o_color == 'b') {
    rbDeleteFixUp(D, x);
  }
}

void rbDeleteFixUp(Dictionary D, Node x) {
  if (D == NULL) {
    printf("ERROR on rbdeletefixup");
    exit(1);
  }
  Node w = D->nil;
  while (x != D->root && x->color == 'b') {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == 'r') {
        w->color = 'b';
        x->parent->color = 'r';
        leftRotate(D, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == 'b' && w->right->color == 'b') {
        w->color = 'r';
        x = x->parent;
      } else {
        if (w->right->color == 'b') {
          w->left->color = 'b';
          w->color = 'r';
          rightRotate(D, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'b';
        w->right->color = 'b';
        leftRotate(D, x->parent);
        x = D->root;
      }
    } else {
      w = x->parent->left;
      if (w->color == 'r') {
        w->color = 'b';
        x->parent->color = 'r';
        rightRotate(D, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == 'b' && w->left->color == 'b') {
        w->color = 'r';
        x = x->parent;
      } else {
        if (w->left->color == 'b') {
          w->right->color = 'b';
          w->color = 'r';
          leftRotate(D, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'b';
        w->left->color = 'b';
        rightRotate(D, x->parent);
        x = D->root;
      }
    }
  }
  x->color = 'b';
}
