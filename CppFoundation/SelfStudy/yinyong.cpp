/*************************************************************************
    > File Name: yinyong.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/14 22:31:20 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

int main01()
{
	int a = 10;  //c编译器分配4个字节内存。。。a内存空间的别名
	int &b = a;  //b就是a的别名。。。
	a = 11;      //直接赋值

	int *p = &a;
	*p = 12;
	printf("a = %d \n",a);

	b = 14;
	printf("a = %d b = %d\n", a, b);
	return 0;
}

