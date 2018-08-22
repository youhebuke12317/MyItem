/**
* @file			54_searchTreeOfK.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 10时57分06秒
*/

#include <iostream>
#include <cstdio>
#include "BinTree.h"
using namespace std;

TreeNode *searchTreeOfKth(TreeNode *root, unsigned int &k) {
	TreeNode *target = NULL;

	if (root -> left)	target = searchTreeOfKth(root -> left, k);
	if (target == NULL && k == 1) target = root, k--;			
	if (root -> right)	target = searchTreeOfKth(root -> right, k);

	return target;
}

TreeNode * KthNode(TreeNode *root, unsigned int k) {
	if (root == NULL || k <= 0) return NULL;
	return searchTreeOfKth(root, k);
}

int main() {
	return 0;
}
