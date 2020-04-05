#include <stdio.h>
#include <stdlib.h>
#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListObj *List;

List newList(void); // Creates and returns a new empty List.
void freeList(List *pL);

int length(List L); // Returns the number of elements in L.
int index(List L);  // Returns index of cursor element if defined, -1 otherwise.
int front(List L);  // Returns front element of L. Pre: length()>0
int back(List L);   // Returns back element of L. Pre: length()>0
int get(List L);    // Returns cursor element of L. Pre: length()>0, index()>=0
int equals(List A, List B);

void clear(List L); // Resets L to its original empty state.
void moveFront(
    List L); // If L is non-empty, sets cursor under the front element,

void moveBack(List L); // If L is non-empty, sets cursor under the back element,

void movePrev(List L); // If cursor is defined and not at front, move cursor one

void moveNext(List L); // If cursor is defined and not at back, move cursor one

void prepend(List L, int data); // Insert new element into L. If L is non-empty,
                                // insertion takes place before front element.

void append(List L, int data); // Insert new element into L. If L is non-empty,

void insertBefore(List L, int data); // Insert new element before cursor.

void insertAfter(List L, int data);

void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L);  // Delete the back element. Pre: length()>0
void delete (List L);

void printList(FILE *out, List L); // Prints to the file pointed to by out, a

List copyList(List L);

// void print_list(List L) {

// List concatList(List A, List B);

#endif
