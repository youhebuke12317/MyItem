/*************************************************************************
    > File Name: static.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 二  1/ 9 01:01:57 2018
 ************************************************************************/

#include <iostream>
using namespace std;

class Test {
	public:
		int getC()
		{
			return c;
		}
		int AddC()
		{
			return c++;
		}

		static void printC()	// 静态成员函数
		{
			cout << "c: " << c << endl;
			// 在静态成员函数中，能调用普通成员属性 或者普通成员函数吗
			// cout << "a: " << a << endl;	// ERROR
		}
	private:
		int a;
		int b;
		static int c;
};

// 静态函数中 不能使用 普通成员变量 和 普成员函数
int Test::c = 10;

void objplaymain_01()
{
	Test b1, b2;

	cout << "b1.c = " << b1.getC() << endl;
	cout << "b2.c = " << b1.getC() << endl;

	b1.AddC();
	b2.AddC();

	cout << "b1.c = " << b1.getC() << endl;
	cout << "b2.c = " << b1.getC() << endl;

	return ;
}

/*
 * 静态成员函数的调用方法
 * */
void objplaymain_02()
{
	Test b1;

	b1.printC();	// 用对象

	Test::printC();	// 类
}


int main()
{
	objplaymain_01();



	return 0;
}
