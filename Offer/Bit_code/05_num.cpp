/**
* @file			05_num.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 16时48分44秒
*/

#include <iostream>
using namespace std;

int printOddTimesNum2(int *arr, int len, int &a, int &b) {
	if (arr == NULL || len < 2)	return -1;
	int sumOR = 0;
	for (int i = 0; i < len; ++i) {
		sumOR ^= arr[i];
	}

	int rightOne = sumOR & (~sumOR + 1);

	for (int i = 0; i < len; ++i) {
		if ((arr[i] >> rightOne & 1)) a ^= arr[i];
		else b ^= arr[i];
	}
	return 0;
}

int main()
{
}
