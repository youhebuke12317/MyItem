/**
* @file			55_TreeDepth.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 11时14分44秒
*/

#include <iostream>
#include <cstdio>
#include "BinTree.h"
using namespace std;

int TreeDepth(TreeNode *root) {
	if (root == NULL)	return 0;
	int nLeft = TreeDepth(root -> left);
	int nRight = TreeDepth(root -> right);
	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

int main() {
	return 0;
}
