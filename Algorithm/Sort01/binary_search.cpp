/**
* @file			binary_search.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月06日 星期一 14时57分56秒
*/

#include <iostream>
using namespace std;


/*
 * 00000000001111111111种找出这个分界点
 * leedcode 278题
 * */

int binary_search(int *num, int n) {
	int head = 0, tail = n, mid;
	while (head < tail) {
		mid = head + (tail - head) >> 2;
		if (num[mid] == 1) tail = mid;
		else head = mid + 1;
	}
	return head;
}
