/**
* @file			03_yunsuan.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 16时18分25秒
*/

#include <iostream>
#include <cstdio>
using namespace std;

int bit_add(int a, int b) {
	int sum = a;
	while (b) {
		sum = a ^ b;
		b = (a & b) << 1;
		a = sum;
	}
	return sum;
}

// 正数二进制取反加1为该正数对应的负数
// 即：(~x + 1) = -x
int bit_negnum(int a, int b) {
	bit_add(a, bit_add(~b, 1));
}

int bit_mutil(int a, int b) {
	int res = 0;
	while (b > 0) {
		if ((b & 1) > 0) res = bit_add(res, a);
		a <<= 1;
		b >>= 1;
	}
	return res;
}

// 除法运算

int main()
{
	int a = 10;
	int b = 20;
	printf("%d\n", bit_mutil(a, b));
}
