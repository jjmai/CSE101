/****************************
 * * Jordan Mai, jmai12
 * * 2020 Spring CSE101,PA1
 * * List.h
 * * Header File for List
 *******************************/

#include <stdio.h>
#include <stdlib.h>
#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListObj *List;

List newList(void);      // Creates and returns a new empty List.
void freeList(List *pL); // Frees all heap memory associated with *pL, and sets

int length(List L); // Returns the number of elements in L.
int index(List L);  // Returns index of cursor element if defined, -1 otherwise.
int front(List L);  // Returns front element of L. Pre: length()>0
int back(List L);   // Returns back element of L. Pre: length()>0
int get(List L);    // Returns cursor element of L. Pre: length()>0, index()>=0
int equals(List A, List B);

void clear(List L);

void moveFront(List L);
void moveBack(List L);
void movePrev(List L);

void moveNext(List L);
void prepend(List L, int data);

void append(List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete (List L);
void printList(FILE *out, List L);

List copyList(List L);
void set(List L, int x);

// List concatList(List A, List B);

#endif
