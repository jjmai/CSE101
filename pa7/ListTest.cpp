/*******************************************
 * Jordan Mai, jmai12
 * CSE101 Spring 2020, PA7
 * ListTest.cpp
 * Test Client for List ADT
 *********************************************/

#include "List.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

  List A, B, C, D, E;
  A.insertAfter(1);
  A.insertAfter(2);
  A.insertAfter(3);
  A.insertAfter(4);
  A.insertAfter(5);
  A.insertAfter(6);
  A.insertAfter(7);
  if (A.size() == 7) {
    cout << A.size() << "\n";
  }
  A.moveNext();
  A.moveNext();
  if (A.position() == 2) {
    cout << "position :" << A.position() << "\n";
  }

  A.insertBefore(8);
  B = A;
  cout << "A graph: " << A << "\n"
       << "B graph: " << B << "\n";

  B.eraseAfter();
  B.eraseBefore();
  C = B;

  cout << "B graph: " << B << "\n"
       << "C graph: " << C << "\n";

  D = A.concat(B);
  cout << "concat :" << D << "\n";

  D.insertAfter(1);
  D.insertAfter(1);
  D.cleanup();
  E = D;

  cout << "Graph D: " << D << "\n"
       << "Graph E: " << E << "\n";

  E.clear();
  if (E.size() == 0) {
    cout << "success clear"
         << "\n";
  }
}
