/**
* @file			04_count1.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 16时44分48秒
*/

#include <iostream>
using namespace std;

int count1(int n) {
	int res = 0;
	while (n) {
		n = n & (n - 1);
		res ++;
	}
	return res;
}
