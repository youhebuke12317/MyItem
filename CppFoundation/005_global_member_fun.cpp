/*************************************************************************
    > File Name: global_member_fun.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 六  1/13 19:10:08 2018
 ************************************************************************/

#include <iostream>
using namespace std;

class Test {
	public:
		Test()
		{
			cout << "无参构造函数" << endl;
		}

		Test(int a, int b)
		{
			cout << "有参构造函数" << endl;
			this->a = a;
			this->b = b;
		}

		~Test()
		{
			cout << "析构函数" << endl;
		}

		Test TestAdd(Test &t2)
		{
			Test temp(this->a + t2.a, this->b + t2.b);
			return temp;
		}

		// t1.TestAdd2(t2)
		// 返回一个引用 相当于返回本身
		Test &TestAdd2(Test &t2)
		{
			this->a = this->a + t2.a;
			this->b = this->b + t2.b;

			return *this; // 把*(&this)
		}

		int getA()
		{
			return a;
		}

		int getB()
		{
			return b;
		}

		void Print()
		{
			cout << "a: " << a << endl;
			cout << "b: " << b << endl;
		}
	private:
		int a;
		int b;
};

// 全局函数的方法
// 把全局函数转成成员函数 少一个参数
// 把成员函数转成全局函数 多一个参数
Test TestAdd(Test &t1, Test &t2)
{
	Test temp(t1.getA() + t2.getA(), t1.getB() + t2.getB());
	// TODO
	return temp;
}

void objplaymain_01()
{
	cout << "======= objplaymain_01 =========" << endl;
	Test t1(1, 2);
	Test t2(3, 4);

	// 全局函数方法
	{
		Test t3;
		t3 = TestAdd(t1, t2);
	}

	// 成员函数方法
	{
		// 先把测试案例写出来
		Test t4 = t1.TestAdd(t2);	//匿名对象直接转成t4
		t4.Print();

		Test t5;
		t5 = t1.TestAdd(t2);	// 匿名对象 复制给t5
		t5.Print();
	}

	return ;
}

void objplaymain_02()
{
	cout << "======= objplaymain_02 =========" << endl;
	Test t1(1, 2);
	Test t2(3, 4);

	// t1 = t1 + t2
	t1.TestAdd2(t2);
	t1.Print();

	
}

int main()
{
	objplaymain_01();

	objplaymain_02();


	return 0;
}
