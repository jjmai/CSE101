#include "List.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

List::Node::Node(int x) {
    data = x;
    next=nullptr;
    prev=nullptr;
}

List::List() {
    frontDummy = new Node(-1); // make new node
    backDummy= new Node(-2);
    beforeCursor=frontDummy;
    afterCursor=backDummy;
    pos_cursor=0;
    num_elements=0;
}

List::List(const List& L) {
    frontDummy = new Node(-1); // make new node
    backDummy= new Node(-1);
    beforeCursor=frontDummy;
    afterCursor=backDummy;
    pos_cursor=0;
    num_elements=0;

    if(L.num_elements !=0) {
        Node *N = L.frontDummy;
        Node *M = new Node(N->data);
        Node *temp;
        frontDummy= M;
        while(N->next != nullptr) {
            temp=N->prev;
            N=N->next;
            M->next = new Node(N->data);
            M->prev=temp;
            M= M->next;
        }
        num_elements=L.num_elements;
    }
}

List::~List() {

}

bool List::isEmpty() {
    return(num_elements==0);
}

int List::size() {
    return(num_elements);
}

int List::position() {
    return pos_cursor;
}

void List::moveFront() {
    pos_cursor=0;
    beforeCursor = frontDummy;
    afterCursor=frontDummy->next;
}

void List ::moveBack() {
    pos_cursor=num_elements;
    afterCursor=backDummy;
    beforeCursor=backDummy->prev;
}

int List::peekNext() {
    if(pos_cursor!=num_elements) {
        return pos_cursor+1;
    }
    return -1;
}

int List::peekPrev() {
    if(pos_cursor!=0 ) {
        return pos_cursor-1;
    }
    return -1;
}

int List::moveNext() {
    if(pos_cursor<num_elements) {
        pos_cursor++;
        beforeCursor=beforeCursor->next;
        afterCursor=afterCursor->next;
    }
    return -1;
}

int List::movePrev() {
    if(pos_cursor>0) {
        pos_cursor--;
        beforeCursor=beforeCursor->prev;
        afterCursor=afterCursor->prev;
    }
    return -1;
}
void List::insertAfter(int x) {
    if(afterCursor==backDummy && beforeCursor==frontDummy) {
        Node * N = new Node(x);
        N->next=afterCursor;
        N->prev=beforeCursor;
        afterCursor=N;
    } else  {
        Node *N= new Node(x);
        N->next=afterCursor;
        beforeCursor->next=N;
        N->prev= beforeCursor;
        N->next->prev = N;
        afterCursor = N;
    }
    num_elements++;
}

void List::insertBefore(int x) {
    if(afterCursor==backDummy && beforeCursor==frontDummy) {
        Node *N=new Node(x);
        N->next = afterCursor;
        N->prev= beforeCursor;
        beforeCursor=N;
    } else {
        Node *N=new Node(x);
        N->next=afterCursor;
        beforeCursor->next=N;
        N->prev=beforeCursor;
        N->next->prev=N;
        beforeCursor=N;
        pos_cursor++;
    }
    num_elements++;
}

void List::eraseAfter() {
    if(pos_cursor<num_elements) {
        beforeCursor->next = afterCursor->next;
        afterCursor->next->prev = beforeCursor;
        afterCursor=afterCursor->next;
        num_elements--;
    }
}

void List::eraseBefore() {
    if(pos_cursor>0) {
        afterCursor->prev= beforeCursor->prev;
        beforeCursor->prev->next = afterCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        num_elements--;
    }
}

int List::findNext(int x) {
    while(pos_cursor!=num_elements) {
        if(afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    return -1;
}

int List::findPrev(int x) {
    while(pos_cursor!=0) {
        if(beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    return -1;
}

void List::cleanup() {
    Node *temp;
    Node *temp2;
    for(temp=frontDummy;temp!=backDummy;temp=temp->next) {
        temp2=temp->next;
        while(temp2!=backDummy) {
            if(temp->data == temp2->data) {
                if(beforeCursor == temp2) {
                    eraseBefore();
                } if(afterCursor== temp2) {
                    eraseAfter();
                } else {
                    Node *next = temp2->next;
                    temp2->next->prev = temp2->prev;
                    temp2->prev->next= temp2->next;
                    num_elements--;
                    temp2 = next;
                }
            } else {
                temp2=temp2->next;
            }
        }
    }
}


List List::concat(const List &L) {
    List  A;
    Node *M=frontDummy;
    Node *N =L.frontDummy;
}

string to_string(int __val) {

}

bool List::equals(const List &R) {
    bool check = false;
    Node *N= nullptr;
    Node *M= nullptr;
    check= (num_elements==R.num_elements);
    N= frontDummy;
    M=R.frontDummy;
    while(check && N!= nullptr) {
        check=(N->data==M->data);
        N=N->next;
        M=M->next;
    }
    return check;
}

void List::print(List &L) {
    Node *A = frontDummy;
    A=A->next;
    while(A!=backDummy) {
        cout << " " << A->data;
        A=A->next;
    }
}

