/*************************************************************************
    > File Name: gouzao_fun.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 六  1/ 6 20:29:49 2018
 ************************************************************************/

#include<iostream>
using namespace std;

/*
 * 构造函数：
 *		无参构造函数
 *		有参构造函数
 *		拷贝构造函数
 *
 * 构造函数的使用及拷贝构造函数的使用时机实例
 * */

class Test
{
	public:
		void printT()
		{
			cout << "a: " << a << ", b: " << b << endl;
			return ;
		}

		Test()
		{
			a = 0;
			b = 0;
			cout << "无参数构造函数，自动被调用" << endl;
			printT();
		}

		Test(int arg)
		{
			a = arg;
			b = 0;
			cout << "有参数构造函数，自动被调用" << endl;
			printT();
		}

		Test(const Test &obj)
		{
			a = obj.a + 100;
			b = obj.b + 100;
			cout << "拷贝数构造函数，作用：用一个对象去初始化另一个对象" << endl;
			printT();
		}

		~Test()
		{
			cout << "我是析构函数，对象生命周期结束时，会被c++编译器自动调用" << endl;
		}
	private:
		int a;
		int b;
	//protected:
};


// 构造函数用用法
void objplaymain01()
{
	cout << "hello: 构造函数用用法" << endl;

	Test t1;			//午餐构造函数的调用
	//Test t2();		//调用无参构造函数的错误用法

	Test t3(3);			//c++编译器自动调用构造函数
	Test t4 = 4;		//c++编译器自动调用构造函数
	Test t5 = Test(5);	//程序员手动调用构造函数

	Test t6 = t1;		//拷贝构造函数的调用

	return ;
}


void printTest(const Test t)
{
	cout << "[copy used time 3] 用实参初始化形参会调用拷贝构造函数" << endl;
}

// 返回一个元素 匿名对象
// 当匿名对象没人接时，会立马会析构
Test getTestObj()
{
	cout << "[copy used time 4] 匿名对象的调用会自动调用拷贝函数" << endl;

	Test t(1);

	return t;
}

void TestNoName()
{
	Test myT1 = getTestObj();	//用匿名对象初始化另一个对象
	
	Test myT2;
	myT2 = getTestObj();	//用匿名对象另一个对象赋值，匿名对象被析构
}

// 拷贝构造函数调用时机
void objplaymain02()
{ 
	Test t1(1);

	Test t2(t1);	// 1 会调用拷贝构造函数
	Test t3 = t1;	// 2 会调用拷贝构造函数
	printTest(t3);	// 3 第三种调用时机
	TestNoName();	// 4 第四种调用时机

}


int main()
{
	cout << "========== objplaymain02 start =========" << endl;

	objplaymain01();

	cout << "========== objplaymain02 start =========" << endl;

	objplaymain02();

	return 0;
}
