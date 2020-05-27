//-----------------------------------------------------------------------------
//// List.h
//// Header file for List ADT. List is a double ended queue with a vertical
//// cursor standing between elements. The cursor position is always defined
//// to be an int in the range 0 (at front) to length of List (at back).
//// An empty list consists of the vertical cursor only, with no elements.
////----------------------------------------------------------------------------

#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported type --------------------------------------------------------------
class List{
  private:
   // private Node struct
        struct Node{
  int data;
        Node* next;
        Node* prev;
        // Node constructor
                 Node(int x);
                     };
     // List fields
     Node* frontDummy;
    Node* backDummy;
    Node* beforeCursor;
    Node* afterCursor;
    int pos_cursor;
    int num_elements;

public:
 
    // Class Constructors & Destructors ----------------------------------------

    // Creates new List in the empty state.
    List();

    // Copy constructor.
    List(const List& L);

    // Destructor
    ~List();
    
    // Access functions --------------------------------------------------------
    
    // isEmpty()
    //Returns true if this List is empty, false otherwise. 
    bool isEmpty();

    // size()
    // Returns the size of this List.
    int size();

    // position()
    // Returns the position of the cursor in this List. The value returned
    // will be in the range 0 to size().
     int position();


    // Manipulation procedures -------------------------------------------------
    
    // moveFront()
    // Moves cursor to position 0 in this List.
