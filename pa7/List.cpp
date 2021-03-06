/*************************************************
 * Jordan Mai, jmai12
 * CSE101 Spring 2020, PA7
 * List.cpp
 * List ADT
 *********************************************/

#include "List.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

List::Node::Node(int x) {
  data = x;
  next = nullptr;
  prev = nullptr;
}
// new List
List::List() {
  frontDummy = new Node(-1); // null dummy
  backDummy = new Node(-2);  // null dummy
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}
// copy constructor
List::List(const List &L) {
  frontDummy = new Node(-1); // make new node
  backDummy = new Node(-2);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;

  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;

  Node *N = L.frontDummy->next;
  while (N != L.backDummy && N != nullptr) {
    this->insertBefore(N->data);
    N = N->next;
  }

  this->moveFront();
}
// Destructor
List::~List() {
  moveFront();
  while (!isEmpty() && num_elements > 0) {
    eraseAfter();
  }
  delete frontDummy;
  delete backDummy;
}

bool List::isEmpty() { return (num_elements == 0); }

int List::size() { return (num_elements); }

int List::position() { return pos_cursor; }

// move cursor
void List::moveFront() {
  pos_cursor = 0;
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
}

void List ::moveBack() {
  pos_cursor = num_elements;
  afterCursor = backDummy;
  beforeCursor = backDummy->prev;
}
// find data after cursor
int List::peekNext() {
  if (pos_cursor != num_elements) {
    return afterCursor->data;
  }
  return -1;
}

int List::peekPrev() {
  if (pos_cursor != 0) {
    return beforeCursor->data;
  }
  return -1;
}

int List::moveNext() {
  if (pos_cursor < num_elements) {
    pos_cursor++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
  }
  return -1;
}

int List::movePrev() {
  if (pos_cursor > 0) {
    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
  }
  return -1;
}
// link node to after cursor
void List::insertAfter(int x) {
  if (num_elements == 0 && afterCursor == backDummy &&
      beforeCursor == frontDummy) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    afterCursor = N;
    num_elements++;
  } else {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
  }
}

void List::insertBefore(int x) {
  if (afterCursor == backDummy && beforeCursor == frontDummy) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
  } else {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
  }
}
// delete after cursor
void List::eraseAfter() {
  if (pos_cursor < num_elements) {
    Node *N = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    delete N;
  }
}

void List::eraseBefore() {
  if (pos_cursor > 0) {
    Node *N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    pos_cursor--;
    num_elements--;
    delete N;
  }
}
// lookup
int List::findNext(int x) {
  while (pos_cursor != num_elements) {
    if (afterCursor->data == x) {
      moveNext();
      return pos_cursor;
    }
    moveNext();
  }
  return -1;
}

int List::findPrev(int x) {
  while (pos_cursor != 0) {
    if (beforeCursor->data == x) {
      movePrev();
      return pos_cursor;
    }
    movePrev();
  }
  return -1;
}
// remove duplicates
void List::cleanup() {
  Node *temp, *temp2;
  int count = 0; // counter for cursor_position

  for (temp = frontDummy->next; temp != backDummy; temp = temp->next) {
    count = 0;
    temp2 = temp->next;
    // iteratively checks if temp==temp2
    while (temp2 != backDummy) {
      if (temp->data == temp2->data) {
        if (temp2 == beforeCursor) {
          temp2 = temp2->next;
          eraseBefore();
        } else if (temp2 == afterCursor) {
          temp2 = temp2->next;
          eraseAfter();
        } else {
          Node *N = temp2;
          temp2->next->prev = temp2->prev;
          temp2->prev->next = temp2->next;
          // change cursor position iff left of cursor
          if (count < pos_cursor) {
            pos_cursor--;
          }
          num_elements--;
          temp2 = temp2->next;
          delete N;
        }
      } else {
        count++;
        temp2 = temp2->next;
      }
    }
  }
}

void List::clear() {
  moveFront();
  while (num_elements > 0) {
    eraseAfter();
  }
}

List List::concat(const List &L) {
  List A = List();
  Node *N = this->backDummy->prev;
  Node *M = L.backDummy->prev;

  while (M != L.frontDummy) {
    A.insertAfter(M->data);
    M = M->prev;
  }
  while (N != frontDummy) {
    A.insertAfter(N->data);
    N = N->prev;
  }
  return A;
}

string List::to_string() {
  Node *N = nullptr;
  string s;

  for (N = frontDummy->next; N != backDummy; N = N->next) {
    s += std::to_string(N->data) + " ";
  }
  s += "\n";
  return s;
}

bool List::equals(const List &R) {
  bool check = false;
  Node *N = nullptr;
  Node *M = nullptr;
  check = (num_elements == R.num_elements);
  N = frontDummy;
  M = R.frontDummy;
  while (check && N != nullptr) {
    check = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return check;
}

ostream &operator<<(ostream &stream, List &L) {
  return stream << L.List::to_string();
}

bool operator==(List &A, const List &B) { return A.List::equals(B); }

// swap all elements
List &List::operator=(const List &L) {
  if (this != &L) {
    List temp = L;
    std::swap(num_elements, temp.num_elements);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
  }
  return *this;
}
