#include "Dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodeObj {
    char *key;
    int value;
    struct NodeObj *left;
    struct NodeObj *right;
    struct NodeObj *parent;
} NodeObj;

typedef NodeObj *Node;

typedef struct DictionaryObj {
    Node root;
    int unique;
    int size;
    Node cursor;
}DictionaryObj;

Node newNode(char *k, int v) {
    Node n = malloc(sizeof(NodeObj));
    n->key=k;
    n->value=v;
    n->left=NULL;
    n->right=NULL;
    return n;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

Dictionary newDictionary(int unique) {
    Dictionary d= malloc(sizeof(struct DictionaryObj));
    d->root=NULL;
    d->size=0;
    d->cursor=NULL;
    if(unique==0) {
        d->unique=0;
    } else {
        d->unique=1;
    }
    return d;
}

void freeDictionary(Dictionary* pD) {
    if(pD!=NULL && *pD !=NULL) {
        makeEmpty(*(pD));
        free(*pD);
        *pD =NULL;
    }
}

int size(Dictionary D) {
    if(D==NULL) {
        printf("ERROR on size");
        exit(1);
    }
    return D->size;
}

int getUnique(Dictionary D) {
    if(D==NULL) {
        printf("ERROR get UNIQU");
        exit(1);
    }
    if(D->unique==0) {
        return 1;
    } else {
        return 0;
    }
}

Node findKey(Node n, KEY_TYPE k) {
    if(n==NULL || KEY_CMP(k,n->key)==0) {
        return n;
    }
    if(strcmp(k,n->key)<0) {
        return findKey(n->left,k);
    } else {
        return findKey(n->right,k);
    }
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
    if(D==NULL) {
        printf("ERROR on lookup");
        exit(1);
    }
    Node n;
    n=findKey(D->root,k);
    if(n!=NULL) {
        return n->value;
    }
    return VAL_UNDEF;
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
    if(D==NULL) {
        printf("ERROR on insert");
        exit(1);
    }
    bool check=false;
    if(getUnique(D)==1) {
        check = true;
    }
    if(getUnique(D)==0) {
        if(lookup(D,k)==VAL_UNDEF) {
            Node A = D->root;
            Node temp = NULL;
            Node new = newNode(k, v);
            while (A != NULL) {
                temp = A;
                if (KEY_CMP(k, A->key) < 0) {
                    A = A->left;
                } else if (KEY_CMP(k, A->key) > 0) {
                    A = A->right;
                }
            }
            new->parent = temp;
            if (temp == NULL) {
                D->root = new;
            } else if (KEY_CMP(new->key, temp->key) < 0) {
                temp->left = new;
            } else {
                temp->right = new;
            }
            D->size++;
        }
    }else if(getUnique(D)==1) {
        Node A = D->root;
        Node temp = NULL;
        Node new = newNode(k, v);
        while (A != NULL) {
            temp = A;
            if (KEY_CMP(k, A->key) < 0) {
                A = A->left;
            } else if (KEY_CMP(k, A->key) >= 0) {
                A = A->right;
            }
        }
        new->parent = temp;
        if (temp == NULL) {
            D->root = new;
        } else if (KEY_CMP(new->key, temp->key) < 0) {
            temp->left = new;
        } else {
            temp->right = new;
        }
        D->size++;
    }
}


void delete(Dictionary D, KEY_TYPE k) {
    if(D==NULL) {
        printf("ERROR on delete");
        exit(1);
    }
    if(lookup(D,k)!=VAL_UNDEF) {
        Node A= D->root;
        Node P=NULL;
        while(A!=NULL) {
            if(KEY_CMP(k,A->key)==0) {
                break;
            } if(KEY_CMP(k,A->key)<0) {
                A=A->left;
            } else {
                A=A->right;
            }
        }
        if(D->cursor==A) {
            D->cursor=NULL;
        }
        if(A==NULL) {
            printf("ERROR on delete");
            exit(1);
        }
        if(A->left ==NULL && A->right ==NULL) {
            if(A==D->root) {
                D->root = NULL;
                freeNode(&A);
            } else {
                P = A->parent;
                if(P->right==A) {
                    P->right=NULL;
                } else {
                    P->left=NULL;
                }
                freeNode(&A);
            }
        } else if(A->right==NULL) {
            if(A==D->root) {
                D->root = A->left;
                freeNode(&A);
            } else {
                P = A->parent;
                if(P->right==A) {
                    P->right=A->left;
                } else {
                    P->left = A->left;
                }
                freeNode(&A);
            }
        } else if(A->left==NULL) {
            if(A==D->root) {
                D->root = A->right;
                freeNode(&A);
            } else {
                P = A->parent;
                if(P->right==A) {
                    P->right = A->right;
                } else {
                    P->left = A->right;
                }
                freeNode(&A);
            }
        } else {
            Node S=A->right;
            while(S->left !=NULL) {
                S=S->left;
            }
            A->key=S->key;
            A->value=S->value;
            P=S->parent;
            if(P->right==S) {
                P->right = S->right;
            } else {
                P->left = S->right;
            }
            freeNode(&S);
        }
        D->size--;
    }
}

void makeEmpty(Dictionary D) {
    if(D==NULL) {
        fprintf(stderr,"ERROR on makeEmpty");
        exit(1);
    }
    D->root=NULL;
    D->size=0;
    D->cursor=NULL;
    beginForward(D);
    for(int i=0;i<size(D);i++) {
        delete(D,currentKey(D));
        next(D);
    }
}

VAL_TYPE beginForward(Dictionary D) {
    if(D==NULL) {
        printf("error on beginforward");
        exit(1);
    }
    if(size(D)>0) {
        Node A = D->root;
        while (A->left != NULL) {
            A = A->left;
        }
        D->cursor=A;
        return A->value;
    }
    return VAL_UNDEF;
}

VAL_TYPE beginReverse(Dictionary D) {
    if(D==NULL) {
        printf("error on beginReverse");
        exit(1);
    }
    if(size(D)>0) {
        Node A=D->root;
        while(A->right!=NULL) {
            A=A->right;
        }
        D->cursor=A;
        return A->value;
    }
    return VAL_UNDEF;
}

KEY_TYPE currentKey(Dictionary D) {
    if(D==NULL) {
        printf("ERROR ON currentKEY");
        exit(1);
    }
    if(D->cursor !=NULL) {
        return D->cursor->key;
    }
    return KEY_UNDEF;
}

VAL_TYPE currentVal(Dictionary D) {
    if(D==NULL) {
        printf("ERROR ON currentKEY");
        exit(1);
    }
    if(D->cursor !=NULL) {
        return D->cursor->value;
    }
    return VAL_UNDEF;
}

VAL_TYPE next(Dictionary D) {
    if(D==NULL) {
        printf("ERROR on next");
        exit(1);
    }
    if(D->cursor ==NULL) {
        return VAL_UNDEF;
    }
    Node A = D->cursor;
    if(A->right !=NULL) {
        Node current=A->right;
        while(current->left!=NULL) {
            current=current->left;
        }
        D->cursor=current;
        return current->value;
    }
    Node temp = A->parent;
    while(temp !=NULL && A == temp->right) {
        A= temp;
        temp= temp->parent;
    }
    if(temp == NULL) {
        D->cursor=NULL;
        return VAL_UNDEF;
    }
    D->cursor = temp;
    return temp->value;
}

VAL_TYPE prev(Dictionary D) {
    if(D==NULL) {
        fprintf(stderr,"ERROR on prev");
        exit(1);
    }
    if(D->cursor ==NULL) {
        return VAL_UNDEF;
    }
    Node A= D->cursor;
    if(A->left !=NULL) {
        Node current = A->left;
        while(current->right!=NULL) {
            current=current->right;
        }
        D->cursor=current;
        return current->value;
    }
    Node temp=A->parent;
    while(temp!=NULL && A==temp->left) {
        A=temp;
        temp=temp->parent;
    }
    if(temp==NULL) {
        D->cursor=temp;
        return VAL_UNDEF;
    }
    D->cursor=temp;
    return temp->value;
}

void printDictionary(FILE* out, Dictionary D) {
    if(D==NULL) {
        printf("ERRORon print");
        exit(1);
    }
    beginForward(D);
    for(int i=0;i<size(D);i++) {
        fprintf(out,"%s %d\n",currentKey(D),currentVal(D));
        next(D);
    }

}







