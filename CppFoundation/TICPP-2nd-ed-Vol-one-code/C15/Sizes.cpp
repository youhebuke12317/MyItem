//: C15:Sizes.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Object sizes with/without virtual functions
#include <iostream>
using namespace std;

class NoVirtual {
  int a;
public:
  void x() const {}
  int i() const { return 1; }
};

class OneVirtual {
  int a;
public:
  virtual void x() const {}
  int i() const { return 1; }
};

class TwoVirtuals {
  int a;
public:
  virtual void x() const {}
  virtual int i() const { return 1; }
};

int main() {
  cout << "int: " << sizeof(int) << endl;		// int: 4
  cout << "NoVirtual: "
       << sizeof(NoVirtual) << endl;			// NoVirtual: 4
  cout << "void* : " << sizeof(void*) << endl;	// void* : 8
  cout << "OneVirtual: "
       << sizeof(OneVirtual) << endl;			// OneVirtual: 16
  cout << "TwoVirtuals: "
       << sizeof(TwoVirtuals) << endl;			// TwoVirtuals: 16
} ///:~
