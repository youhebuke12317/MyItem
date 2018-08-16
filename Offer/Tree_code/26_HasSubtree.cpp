/**
* @file			26_HasSubtree.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 10时07分34秒
*/

#include <iostream>
#include <cstdio> 
#include "BinTree.h"
using namespace std;

bool GetEqualNode(TreeNode *root1, TreeNode *root2) {
	if (root2 == NULL) 	return true;
	if (root1 == NULL)	return false;
	if (root1 -> val != root2 -> val) return false;
	return GetEqualNode(root1 -> left, root2 -> left) &&
		GetEqualNode(root1 -> right, root2 -> right);
}

bool HasSubtree(TreeNode *root1, TreeNode *root2) {
	bool result = false;
	
	if (root1 && root2) {
		if (root1 -> val == root2 -> val) result = GetEqualNode(root1, root2);
		if (!result) HasSubtree(root1 -> left, root2 -> left);
		if (!result) HasSubtree(root1 -> right, root2 -> right);
	}
	
	return result;
}

int main() {
	return 0;
}
