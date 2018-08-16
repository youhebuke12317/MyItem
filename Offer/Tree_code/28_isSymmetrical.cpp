/**
* @file			28_isSymmetrical.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 17时07分17秒
*/

#include <iostream>
#include "BinTree.h"
using namespace std;

bool __isSymmetrical(TreeNode *root1, TreeNode *root2) {
	if (!root1 && !root2) return true;
	if (root1 || root2)	return false;
	if (root1 -> val != root2 -> val) return false;
	return __isSymmetrical(root1 -> left, root2 -> right) &&
		__isSymmetrical(root1 -> right, root2 -> left);
}

bool isSymmetrical(TreeNode *root) {
	__isSymmetrical(root, root);
}

int main() {
	return 0;
}
