/*************************************************************************
    > File Name: gouzao_list_fun.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/ 7 10:59:13 2018
 ************************************************************************/

#include <iostream>
using namespace std;

/*
 * 对象初始化列表
 * */

class A {
	public:
		A(int _a)
		{
			a = _a;
			cout << "A 构造函数 a: " << a << endl;
		}

		~A()
		{
			cout << "A 析构函数 a: " << a << endl; 
		}
	private:
		int a;
};

// 构造函数的初始化列表 解决：在B类中 组合了一个A类对象（A类设计了构造函数）
// 根据构造函数的调用规则 设计A的构造函数，必须要用；没有机会初始化
class B {
	public:
		B(int _b1, int _b2): a1(100), a2(200), c(0)
		{
			cout << "B 析构函数 01" << endl; 
			b1 = _b1;
			b2 = _b2;
		}

		B(int _b1, int _b2, int m, int n): a1(m), a2(n), c(0)
		{
			cout << "B 析构函数 02" << endl; 
			b1 = _b1;
			b2 = _b2;
		}

		~B()
		{
			cout << "B 析构函数" << endl;
		}
	private:
		int b1;
		int b2;
		A a2;	// 初始化时跟定义顺序有关
		A a1;
		const int c;
};

// 2 调用顺序
//		先执行 被组合对象的构造函数
//		如果组合对象有多个，按照定义顺序，而不是按照初始化列表的顺序
//
//		析构函数：和构造函数的调用顺序相反
//
// 3 被组合对象的构造顺序 与定义有关，与初始化列表的顺序无关
//
// 4 初始化列表 用来给const属性复制
void objplaymain()
{
	cout << "obj_a1(10)" << endl;
	A obj_a1(10);

	cout << "obj_b1(1, 2)" << endl;
	B obj_b1(1, 2);

	cout << "obj_b2(1, 2, 100, 200)" << endl;
	B obj_b2(1, 2, 3, 4);

	return ;
}

int main()
{
	objplaymain();

	return 0;
}

