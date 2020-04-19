/****************************
 *  * Jordan Mai, jmai12
 *   * 2020 Spring CSE101,PA1
 *    * List.h
 *     * Header File for List
 ******************************/

#include <stdio.h>
#include <stdlib.h>
#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListObj *List;

List newList(void);      // Creates and returns a new empty List.
void freeList(List *pL); // Frees all heap memory associated with *pL, and sets

long length(List L); // Returns the number of elements in L.
long index(List L); // Returns index of cursor element if defined, -1 otherwise.
long front(List L); // Returns front element of L. Pre: length()>0
long back(List L);  // Returns back element of L. Pre: length()>0
long get(List L);   // Returns cursor element of L. Pre: length()>0, index()>=0
long l_equals(List A, List B);

void clear(List L);

void moveFront(List L);
void moveBack(List L);
void movePrev(List L);

void moveNext(List L);
void prepend(List L, long data);

void append(List L, long data);

void insertBefore(List L, long data);

void insertAfter(List L, long data);

void deleteFront(List L);
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete (List L);
void printList(FILE *out, List L);

List copyList(List L);

void set(List L, long x);

// List concatList(List A, List B);

#endif
