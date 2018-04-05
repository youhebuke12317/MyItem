/*************************************************************************
    > File Name: operate_re.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/14 12:36:30 2018
 ************************************************************************/

#include <iostream>
using namespace std;

// 注意：不能重载的运算符：.  ::  *  ?:  sizeof

class Complex {
	public: 
		int a;
		int b;
		friend Complex & operator++(Complex &c1);
		friend Complex   operator++(Complex &c1, int);
	public:
		Complex()
		{
			a = 0;
			b = 0;
		}

		Complex(int a, int b)
		{
			this -> a = a;
			this -> b = b;
		}
	
		Complex & operator--()
		{
			cout << "前置--操作符 用成员函数实现" << endl;
			this -> a --;
			this -> b --;
			this -> c --;

			return *this;
		}

		Complex   operator--(int)
		{
			cout << "前置--操作符 用成员函数实现" << endl;
			Complex tmp = *this;
			this -> a --;
			this -> b --;
			this -> c --;

			return tmp;
		}

		void myPrint()
		{
			cout << "a + bi = " << a << " + " << b << "i" << endl;
			cout << "c = " << c << endl;
			return ;
		}
	private:
		int c;
};


// 前置++操作符 用全局函数实现
Complex & operator++(Complex &c1)
{
	cout << "前置++操作符 用全局函数实现" << endl;
	c1.a++;
	c1.b++;
	c1.c++;
	return c1;
}

// 后置++操作符 用全局函数实现	 使用占位符
Complex   operator++(Complex &c1, int)
{
	cout << "前置++操作符 用全局函数实现" << endl;
	Complex tmp = c1;
	c1.a++;
	c1.b++;
	c1.c++;
	return tmp;
}


// 一元运算符重载
void objplaymain_03()
{
	Complex c1(1, 2), c2(3, 4);
	// 前置++操作符 用全局函数实现
	// Complex & operator++(Complex &c1);
	c1.myPrint();
	++c1;
	c1.myPrint();

	// 前置--操作符 用成员函数实现
	// Complex & operator--();
	c1.myPrint();
	--c1;
	c1.myPrint();

	// 后置++操作符 用全局函数实现
	// Complex  operator++(Complex &c1, int);
	c1.myPrint();
	c1++;
	c1.myPrint();

	// 后置--操作符 用成员函数实现
	// Complex  operator--(int);
	c1.myPrint();
	c1--;
	c1.myPrint();
	return ;
}

int main()
{
	objplaymain_03();

	return 0;
}
