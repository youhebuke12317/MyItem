/**
* @file			33_verifySquenceOfBST.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月16日 星期四 19时25分04秒
*/

#include <iostream>
#include "BinTree.h"
using namespace std;

bool verifySquenceOfBST(int *num, int len) {
	if (num == NULL || len <= 0) return false;

	int root = num[len - 1];
	int index = len - 1;

	for (int i = 0; i < len - 1; ++i) {
		if (num[i] > root) {
			index = i;
			break;
		}
	}

	for (int j = index; j < len -1; ++j) {
		if (num[j] < root) return false;
	}

	bool left = true, right = true;
	if (index > 0) left = verifySquenceOfBST(num, index);
	if (index < len - 1) right = verifySquenceOfBST(num + index, len - index - 1);

	return (left && right);
}


int main() {
	return 0;
}
