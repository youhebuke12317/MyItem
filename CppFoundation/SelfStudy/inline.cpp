/*************************************************************************
    > File Name: inline.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/14 23:24:16 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

#define MYFUNC(a, b) ((a) < (b) ? (a) : (b))

inline int myfunc(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int a = 1;
	int b = 3;
	int c = myfunc(++a, b);  //头疼系统
	//int c = MYFUNC(++a, b);

	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);

	return 0;
}
