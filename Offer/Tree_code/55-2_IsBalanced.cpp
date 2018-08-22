/**
* @file			55-2_IsBalanced.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 11时24分22秒
*/

#include <iostream>
#include <cstdio>
#include "BinTree.h"
using namespace std;

bool IsBalanced_bad(TreeNode *root) {
	if (root == NULL)	return true;

	int nLeft = IsBalanced_bad(root -> left);
	int nRight = IsBalanced_bad(root -> right);
	int diff = nLeft - nRight;
	if (diff > 1 || diff < -1) return false;
	return IsBalanced_bad(root -> left) && IsBalanced_bad(root -> right);
}

bool __IsBalanced_good(TreeNode *root, int &depth) {
	if (root == NULL) {
		depth = 0;
		return true;
	}

	int left, right;
	if (__IsBalanced_good(root -> left, depth) && 
			__IsBalanced_good(root -> right, depth)) 
	{
		int diff = left - right;
		if (diff <= 1 || diff >= -1) {
			depth = 1 + (left > right ? left : right);
			return true;
		}	
	}
	return false;
}


bool IsBalanced_good(TreeNode *root) {
	int depth = 0;
	return __IsBalanced_good(root, depth);
}

int main() {
	return 0;
}
