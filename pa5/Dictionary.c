#include "Dictionary.h"
#include <string.h>

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
    int key;
    int value;
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
    d->key=0;
    d->value=0;
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

    }
}

int size(Dictionary D) {
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
    if(getUnique(D)==0) {
        Node A= D->root;
        Node temp=NULL;
        Node new =newNode(k,v);
        while(A!=NULL) {
            temp=A;
            if(KEY_CMP(k, A->key)<0) {
                A=A->left;
            } else {
                A=A->right;
            }
        }
        new->parent=temp;
        if(temp==NULL) {
            D->root=new;
        }else if(KEY_CMP(new->key,temp->key)<0) {
            temp->left=new;
        } else {
            temp->right=new;
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
        while(A!=NULL) {
            if(KEY_CMP(k,A->key)==0) {
                break;
            } if(KEY_CMP(k,A->key)<0) {
                A=A->left;
            } else {
                A=A->right;
            }
        }
        if(A->left==NULL) {
            if(A->parent==NULL) {

            }
        }
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

Node Transverse();

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
        Node current=D->cursor->right;
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

void printDictionary(FILE* out, Dictionary D) {
    if(D==NULL) {
        printf("ERRORon print");
        exit(1);
    }


}







