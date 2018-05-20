//: C14:CopyConstructor.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Correctly creating the copy-constructor
// 2018-05-18 zl comment


#include <iostream>
using namespace std;

class Parent {
  int i;	// 私有成员变量
public:
  // 有参构造函数
  Parent(int ii) : i(ii) {
    cout << "Parent(int ii)\n";
  }

  // 拷贝构造函数
  Parent(const Parent& b) : i(b.i) {
    cout << "Parent(const Parent&)\n";
  }

  // 无参构造函数
  Parent() : i(0) { cout << "Parent()\n"; }

  // 友元函数 --- <<运算符重载 
  friend ostream&
    operator<<(ostream& os, const Parent& b) {
    return os << "Parent: " << b.i << endl;
  }
};

class Member {
  int i;	// 私有成员变量
public:
  // 有参构造函数
  Member(int ii) : i(ii) {
    cout << "Member(int ii)\n";
  }

  // 拷贝构造函数
  Member(const Member& m) : i(m.i) {
    cout << "Member(const Member&)\n";
  }

  // 友元函数 --- <<运算符重载
  friend ostream&
    operator<<(ostream& os, const Member& m) {
    return os << "Member: " << m.i << endl;
  }
};

class Child : public Parent {
  int i;		// 私有成员变量
  Member m;		// 私有成员变量
public:
  // 有参构造函数
  Child(int ii) : Parent(ii), i(ii), m(ii) {
    cout << "Child(int ii)\n";
  }

#ifdef COPYCON_NULL
  // 子类没有拷贝构造函数的时候
  {
	// 不添加的时候是这样的:
	// Parent(int ii)
	// Member(int ii)
	// Child(int ii)
	// calling copy-constructor: 
	// Parent(const Parent&)		---->
	// Member(const Member&)
	// values in c2:
	// Parent: 2
	// Member: 2
	// Child: 2
  }
#elif COPYCON_ERROR
  // 拷贝构造函数 -- 不对
  Child(const Child &c) : i(c.i), m(c.m) {
	// 添加该拷贝构造函数的打印
	// Parent(int ii)
	// Member(int ii)
	// Child(int ii)
	// calling copy-constructor: 
	// Parent()	 					---->
	// Member(const Member&)
	// values in c2:
	// Parent: 0					<----
	// Member: 2
	// Child: 2
	
  };
#else
  // 拷贝构造函数正确的写法应该这样:
  Child(const Child &c) : Parent(c), i(c.i), m(c.m) {	// Parent(c) ->> 向上类型转换 --> 引用或者指针
	  cout << "Child(Child &)\n";
	  // Parent(int ii)
	  // Member(int ii)
	  // Child(int ii)
	  // calling copy-constructor: 
	  // Parent(const Parent&)
	  // Member(const Member&)
	  // Child(Child &)				-----
	  // values in c2:
	  // Parent: 2
	  // Member: 2
	  // Child: 2
  }
#endif

  // 友元函数 --- <<运算符重载
  friend ostream&
    operator<<(ostream& os, const Child& c){
    return os << (Parent&)c << c.m
              << "Child: " << c.i << endl;
  }
};

int main() {
  Child c(2);
  cout << "calling copy-constructor: " << endl;
  Child c2 = c; // Calls copy-constructor
  cout << "values in c2:\n" << c2;
} ///:~
