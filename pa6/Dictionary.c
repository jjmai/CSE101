#include "Dictionary.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void leftRotate(Dictionary D, KEY_TYPE x);
void rightRotate(Dictionary D, KEY_TYPE x);
void rbInsert(Dictionary D, KEY_TYPE z);
void rbInsertFixUp(Dictionary D, KEY_TYPE z );
void rbDelete(Dictionary D, KEY_TYPE z);

typedef struct NodeObj {
    char *key;
    int *value;
    char color;
    struct NodeObj *left;
    struct NodeObj *right;
    struct NodeObj *parent;
} NodeObj;

typedef NodeObj *Node;

void pre(FILE *out,Dictionary D, Node z);
void post(FILE *out,Dictionary D, Node z);
void rbTransplant(Dictionary D,Node x, Node y);
void rbDeleteFixUp(Dictionary D, Node x);

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
    n->parent=NULL;
    return n;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

void deleteAll(Node R) {
    if (R != NULL) {
        deleteAll(R->left);
        deleteAll(R->right);
        freeNode(&R);
    }
}

Dictionary newDictionary(int unique) {
    Dictionary d = malloc(sizeof(struct DictionaryObj));
    assert(d);
    d->size = 0;
    d->nil=newNode(KEY_UNDEF,VAL_UNDEF);
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
Node findKey(Node n, KEY_TYPE k) {
    if (n == NULL || KEY_CMP(k, n->key) == 0) {
        return n;
    }
    if (strcmp(k, n->key) < 0) {
        return findKey(n->left, k);
    } else {
        return findKey(n->right, k);
    }
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
        printf("ERROR on lookup");
        exit(1);
    }
    Node n=NULL;
    n = findKey(D->root, k);
    if (n != NULL) {
        return n->value;
    }
    return VAL_UNDEF;
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
    if (D == NULL) {
        printf("ERROR on insert");
        exit(1);
    }
    rbInsert(D,k);
    D->size++;

}

void delete (Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
        printf("ERROR on delete");
        exit(1);
    }
    rbDelete(D,k);
    D->size--;


}

void makeEmpty(Dictionary D) {
    if (D == NULL) {
        fprintf(stderr, "ERROR on makeEmpty");
        exit(1);
    }
    deleteAll(D->root);
    D->root = NULL;
    D->size = 0;
    D->cursor = NULL;
}

VAL_TYPE beginForward(Dictionary D) {
    if (D == NULL) {
        printf("error on beginforward");
        exit(1);
    }
    if (size(D) > 0) {
        Node A = D->root;
        while (A->left != NULL) {
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
        while (A->right != NULL) {
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
    if (D->cursor != NULL) {
        return D->cursor->key;
    }
    return KEY_UNDEF;
}

VAL_TYPE currentVal(Dictionary D) {
    if (D == NULL) {
        printf("ERROR ON currentKEY");
        exit(1);
    }
    if (D->cursor != NULL) {
        return D->cursor->value;
    }
    return VAL_UNDEF;
}

VAL_TYPE next(Dictionary D) {
    if (D == NULL) {
        printf("ERROR on next");
        exit(1);
    }
    if (D->cursor == NULL) {
        return VAL_UNDEF;
    }
    Node A = D->cursor;
    if (A->right != NULL) {
        Node current = A->right;
        while (current->left != NULL) {
            current = current->left;
        }
        D->cursor = current;
        return current->value;
    }
    Node temp = A->parent;
    while (temp != NULL && A == temp->right) {
        A = temp;
        temp = temp->parent;
    }
    if (temp == NULL) {
        D->cursor = NULL;
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
    if (D->cursor == NULL) {
        return VAL_UNDEF;
    }
    Node A = D->cursor;
    if (A->left != NULL) {
        Node current = A->left;
        while (current->right != NULL) {
            current = current->right;
        }
        D->cursor = current;
        return current->value;
    }
    Node temp = A->parent;
    while (temp != NULL && A == temp->left) {
        A = temp;
        temp = temp->parent;
    }
    if (temp == NULL) {
        D->cursor = temp;
        return VAL_UNDEF;
    }
    D->cursor = temp;
    return temp->value;
}

void printDictionary(FILE* out, Dictionary D, const char* ord) {
    if(KEY_CMP(ord,"pre")==0) {
        pre(out,D,D->root);
    } else if(KEY_CMP(ord,"in")==0) {
        beginForward(D);
        for(int i=0;i<size(D);i++) {
            printf("%s \n",currentKey(D));
            next(D);
        }
    }else if(KEY_CMP(ord,"post")==0) {
        post(out,D,D->root);
    }
}
void pre(FILE *out,Dictionary D, Node z) {
    if(z==NULL) {
        return;
    }
    printf("%s\n",z->key);
    pre(out,D,z->left);
    pre(out,D,z->right);
}
void post(FILE *out,Dictionary D, Node z) {
    if(z==NULL) {
        return;
    }
    post(out,D,z->left);
    post(out,D,z->right);
    printf("%s\n",z->key);
}

void rbInsert(Dictionary D, KEY_TYPE z) {
    if(D==NULL) {
        printf("ERROR on rbinsert");
        exit(1);
    }
    if(getUnique(D)==1) {
        Node y= D->nil;
        Node A= D->root;
        Node new = newNode(z,NULL);
        while(A != D->nil) {
            y=A;
            if(KEY_CMP(z,A->key)<0) {
                A=A->left;
            } else if(KEY_CMP(z,A->key)>=0) {
                A=A->right;
            }
        }
        new->parent=y;
        if(y==D->nil) {
            new->color='b';
            D->root=new;
        } else if(KEY_CMP(new->key,y->key)<0) {
            y->left=new;
        } else {
            y->right =new;
        }
        new->left=D->nil;
        new->right =D->nil;
        new->color='r';
        rbInsertFixUp(D,new->key);
            }
            }
