/*************************************************************************
    > File Name: 016_inherit_yufa.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  3/ 4 13:47:58 2018
    > Brief: 继承语法 
 ************************************************************************/

#include <iostream>
using namespace std;

// public		修饰的成员变量 方法 在类的外部 类的内部都能使用
// protected	修饰的成员变量 方法 在类的内部使用 不能在类的外部使用 但可以在继承的子类中可用
// private		修饰的成员变量 方法 只能在类的内部使用 不能在类的外部使用
//
// 派生类的访问控制（三看原则）：
//		1 看调用语句 写在子类的外部还是外部
//		2 看子类如何从父类中继承（public protected private）
//		3 看父类中的访问级别（public protected private）
class Parent
{
	public:
		int a;

		void print() {
			cout << "a = " << a << ", b = " << b << endl; 
			return ;
		}
	protected:
		int b;
	private:
		int c;
};

/* 共有继承 */
class Child : public Parent			// 共有继承
// class Child : private Parent		// 私有继承
// class Child : protected Parent	// 保护继承
{
	public:
		int d;

		void UseVar() {
			a = 0;	// OK
			b = 0;	// OK
			// c = 0;	// ERROR 
		}
	protected:
		int f;
	private:
		int g;
};

int main()
{
	Child t1;
	t1.a = 1;	// OK
	// t1.b = 2;	// ERROR
	// t1.c = 3;	// ERROR

	t1.print();

	return 0;
}
