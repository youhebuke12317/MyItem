/*************************************************************************
    > File Name: const.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/14 22:15:15 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

int main01()
{
	int i = 42;
	const int &r1 = i;		//正确 //const引用 使用变量a初始化
	
	i = 50;					// 
	// r1 = 50;				// //通过引用修改a,对不起修改不了
	printf("i = %d, r1 = %d\n", i, r1);

	const int &r2 = 42;		//正确，r1  是const引用
	const int &r3 = r1 * 2;	//正确，r1  是const引用
	// int &r4 = 32;		//错误，r4不是const引用
	
	return 0;
}

int main02()
{
	int a = 10;
	const int &b = a;

	int *p = (int *)&b;
	// b = 11;		//err
	*p = 11;	    //只能用指针来改变了

	cout<<"b--->"<<a<<endl;
	printf("a:%d\n", a);
	printf("b:%d\n", b);
	printf("&a:%d(%p)\n", &a, &a);
	printf("&b:%d(%p)\n", &b, &b);

	return 0;
}
