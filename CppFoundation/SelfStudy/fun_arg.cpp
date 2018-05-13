/*************************************************************************
    > File Name: fun_arg.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/14 23:35:30 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

void myPrint(int x = 3)
{
	printf("x:%d\n", x);
}

int func(int a, int b, int )
{
	return a + b;
}

int main01()
{
    // func(1, 2); //可以吗？
	printf("func(1, 2, 3) = %d\n", func(1, 2, 3));

	return 0;
}

int main()
{
	//myPrint();
	main01();

	return 0;
}
