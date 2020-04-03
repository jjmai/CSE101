#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

List newList(void);      // Creates and returns a new empty List.

void freeList(List *pL); // Frees all heap memory associated with *pL, and sets
                         // *pL to NULL.
                         //
