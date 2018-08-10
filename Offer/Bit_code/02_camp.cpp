/**
* @file			02_camp.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 15时53分40秒
*/

#include <iostream>
using namespace std;

/*
 * 不使用任何比较判断找出两个数中较大的数
 */

// a - b的值可能溢出
int getmax(int a, int b) {
	int c = a - b;
	int scA = ((c >> 31) & 1 ^ 1);
	int scB = scA ^ 1;
	return a * scA + b * scB;
}

// 解决上一个问题
int getmax2(int a, int b) {
	int c = a - b;
	int sa = ((a >> 31) & 1 ^ 1);	// 判断是正还是负: 1为正, 0位负
	int sb = ((b >> 31) & 1 ^ 1);	// 判断是正还是负: 1为正, 0位负
	int sc = ((c >> 31) & 1 ^ 1);	// 判断是正还是负: 1为正, 0位负
	int difsab = sa ^ sb;			// a与b符号是否相同: 1表示不同, 0代表相同
	int samsab = difsab ^ 1;		// a与b符号是否相同: 1表示不同, 0代表相同

	/*
	 * 如果ab同号: difsab = 0, samsab = 1
	 * 		a - b >= 0 返回a
	 * 		a - b < 0  返回b
	 *
	 * 如果ab不同号: difsab = 1, samsab = 0
	 * 		a >= 0 返回b
	 * 		b >= 0 返回a
	 * */
	int returnA = difsab * sa + samsab * sc;	
	int returnB = returnA ^ 1;
	return (a * returnA + b * returnB);
}


int main()
{
	return 0;
}
