/**
* @file			07_01_swap.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 15时50分04秒
*/

#include <iostream>
using namespace std;

// 不适用任何额外变量交换两个整数的值

void swap(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	b = a ^ b;
}

int main()
{
	return 0;
}
