/*************************************************************************
    > File Name: new_delete.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 一  1/ 8 00:21:02 2018
 ************************************************************************/

#include <iostream>
using namespace std;

/*
 * 1 简介
 *		malloc	free
 *		new		delete
 * 2 new基础类型变量 分配数组变量 分配类对象
 * */


/*
 * 分配基础类型变量
 * */
void objplaymain_01()
{
	cout << ">>>>> 分配基础类型变量>>>>>>>>>>" << endl;
	// 
	int *p1 = (int *)malloc(sizeof(int));
	*p1 = 10;
	free(p1);

	int *p2 = new int;	//分配基础类型
	*p2 = 20;
	delete p2;

	int *p3 = new int(30);
	cout << "*p3 = " << *p3 << endl;
	delete p3;

	return ;
}

/*
 * 分配数组
 * */
void objplaymain_02()
{
	cout << ">>>>> 分配数组变量>>>>>>>>>>" << endl;

	// c语言分配数组
	int *p1 = (int *)malloc(sizeof(int) * 10);	// int array
	p1[0] = 1;
	free(p1);

	// c++分配数组
	int *pArray = new int[10];	
	pArray[0] = 2;
	delete [] pArray;	// 数组不要把'[]'忘记

	return ;
}

/*
 * 分配对象
 * */
class Test {
	public:
		Test(int _a)
		{
			a = _a;
			cout << "构造函数" << endl;
		}

		~Test()
		{
			cout << "析构函数" << endl;
		}
	private:
		int a;
};

/*
 * malloc 与 free不会调用类的构造函数和析构函数
 * */
void objplaymain_03()
{
	cout << ">>>>> 分配对象 >>>>>>>>>>" << endl;

	// C语言
	Test *pT1 = (Test *)malloc(sizeof(Test));
	free(pT1);

	Test *pT2 = new Test(10);
	delete pT2;

	return ;
}

int main()
{
	objplaymain_01();
	objplaymain_02();
	objplaymain_03();

	return 0;
}
