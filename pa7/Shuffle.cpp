#include "List.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void shuffle(List &D);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Error too few arguments";
    exit(1);
  }

  int n = 0;
  string s = argv[1];
  n = stoi(s);

  List l = List();
  List ll;

  cout << "deck size \t"
       << "shuffle count \n";
  cout << "------------------------------\n";

  for (int i = 1; i <= n; i++) {
    int count = 0;
    for (int j = 0; j < i; j++) {
      l.insertAfter(j);
      l.moveNext();
    }
    l.moveFront();
    for (int j = 0; j < i; j++) {
      ll.insertBefore(l.peekNext());
      l.moveNext();
    }
    shuffle(l);
    count = 1;
    while (!ll.equals(l)) {
      shuffle(l);
      count++;
    }
    cout << i << " \t\t" << count << "\n";
    l.clear();
    ll.clear();
  }
}

void shuffle(List &D) {
  List A = List();
  List B = List();
  List C = List();
  D.moveFront();
  for (int i = 0; i < D.size() / 2; i++) {
    A.insertBefore(D.peekNext());
    D.moveNext();
  }
  for (int i = D.size() / 2; i < D.size(); i++) {
    B.insertBefore(D.peekNext());
    D.moveNext();
  }
  D.clear();
  A.moveFront();
  B.moveFront();
  for (int i = 0; i < B.size(); i++) {
    if (B.peekNext() != -1) {
      C.insertBefore(B.peekNext());
      B.moveNext();
    }
    if (A.peekNext() != -1) {
      C.insertBefore(A.peekNext());
      A.moveNext();
    }
  }
  C.moveFront();
  for (int i = 0; i < C.size(); i++) {
    D.insertBefore(C.peekNext());
    C.moveNext();
  }
}
