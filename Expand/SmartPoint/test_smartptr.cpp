/**
* @file			test_智能指针.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年07月27日 星期五 19时22分19秒
*/

#include <iostream>
#include "smartptr.h"
using namespace std;

int main()
{
	SmartPtr<int> p1(new int(0));
	p1 = p1;

	SmartPtr<int> p2(p1);

	SmartPtr<int> p3(new int(1));
	p3 = p1;

	return 0;
}
