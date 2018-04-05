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
	public:
		Complex()
		{
			a = 0;
			b = 0;
		}

		Complex(int a, int b)
		{
			this->a = a;
			this->b = b;
		}

		// 成员函数的运算符重载
		Complex operator-(Complex &c1)
		{
			cout << "成员函数的运算符重载" << endl;
			Complex temp(1, 2);
			return temp;
		}

		// 友元函数实现全局函数的运算符重载
		friend Complex operator* (Complex &c1, Complex &c2);

		void myPrint()
		{
			cout << a << " + " << b << "i" << endl;
			return ;
		}
	private:
		int c;
};

/*
 * 全局函数 类成员函数方法实现运算符重载步骤
 *	1) 要承认操作符重载是一个函数 写出函数名
 *	2）更具操作数 写出函数参数
 *	3）根据业务 完善函数返回值及实现函数业务
 * */
// 全局函数
Complex myAdd(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);
	return temp;
}

// 函数名升级
Complex operator+(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);
	return temp;
}

void objplaymain_01()
{
	Complex c1(1, 2), c2(3, 4);

	// 全局函数实现
	Complex c3;
	c3 = myAdd(c1, c2);
	c3.myPrint();

	// 运算符重载关键字
	Complex c4;
	c4 = operator+(c1, c2);
	c4.myPrint();

	// 运算符重载
	Complex c5;
	c5 = c1 + c2;
	c5.myPrint();

	// 结论：
	//		1 运算符重载的本质 是 函数调用

}

// 友元函数实现全局函数的运算符重载
Complex operator* (Complex &c1, Complex &c2)
{
	cout << "友元函数实现全局函数的运算符重载" << endl;
	Complex temp(1, 2);
	return temp;
}

#if 0
// 疑问：为什么不能使用这个呢
// 友元函数实现成员函数的运算符重载
Complex Complex::operator<< (Complex &c1)
{
	cout << "友元函数实现成员函数的运算符重载" << endl;
	Complex temp(1, 2);
	return temp;
}
#endif

// 二元运算符重载
void objplaymain_02()
{
	Complex c1(1, 2), c2(3, 4);

	// 1 全局函数法 实现 + 运算符重载
	// Complex operator+(Complex &c1, Complex &c2);

	// 2 c成员函数法实现 + 运算符重载
	// Complex operator+(Complex &c2);
	//c1.operator+(c2);
	Complex c3 = c1 + c2;
	Complex c4 = c1 - c2;
	Complex c5 = c1 * c2;

	return ;
}


int main()
{
	objplaymain_01();

	objplaymain_02();

	return 0;
}
