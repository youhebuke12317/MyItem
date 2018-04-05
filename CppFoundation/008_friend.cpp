/*************************************************************************
    > File Name: friend.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/14 11:10:05 2018
 ************************************************************************/

#include <iostream>
using namespace std;

class A {
	public:
		// B类是A类的好朋友 在B中可以访问A类的私有成员 私有函数
		friend class B;
		// 1 声明的位置和 public private 的位置没有关系
		// 2 函数modifyA 是 类A的好朋友
		friend void modifyA(A *pA, int _a);	// 元友函数

		A(int a, int b){
			this->a = a;
			this->b = b;
		}

		int getA() {
			return a;
		}

	private:
		int a;
		int b;
};

void modifyA(A *pA, int _a)
{
	pA->a = _a;
}

class B {
	public:
		void Set(int a) {
			Aobject.a = a;
		}
		 void printB() {
			cout << Aobject.a << endl;
		 }
	private:
		A Aobject;
};

// 友元函数实例
void objplaymain_01()
{
	A a(1, 2);
	cout << a.getA() << endl;

	modifyA(&a, 100);
	cout << a.getA() << endl;

	return ;
}

// 友元类实例
void objplaymain_02()
{
	B b2;
	b1.Set(300);
	b1.printB();

	return ;
}


// 为什么设计友元类函数
// 1 1.java --> 1.class(字节码) ==> 反射机制分析1.class 找到类对象 修改类的>    私有属性
// 反射机制 成为一种标准。。。jdk。。。sun做成标准。。jdk中api函数中有体现

// 2 2.cpp ==> 汇编
// 预编译 编译 连接 生成  
// gcc -E / gcc -s /

// 3 开了个后门  friend

int main()
{
	objplaymain_01();
	objplaymain_02();
	return 0;
}

/*
 * gcc -E hello.c -o hello.i (预编译)
 * gcc -S hello.i -o hello.s (编译)
 * gcc -c hello.s -o hello.o (汇编)
 * gcc -d hello.o -o hello (链接)
 * 以上四个步骤，可合成一个步骤
 *
 * gcc hello.c -o hello (直接编译链接成可执行目标文件)
 * gcc -c hello.c 或 gcc -c hello.c -o hello.o (编译生成可重定向目标文件)
 * */
