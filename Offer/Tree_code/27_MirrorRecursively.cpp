/**
* @file			27_MirrorRecursively.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 10时40分04秒
*/

#include <iostream>
#include <stack>
#include "BinTree.h"
using namespace std;

//前序遍历 - 交换
void MirrorRecursively(TreeNode *root) {
	if (!root) return;
	if ((!root -> left) && (!root -> right)) return;

	TreeNode *pTmp = root -> left;
	root -> left = root -> right;
	root -> right = pTmp;

	if (root -> left) MirrorRecursively(root -> left);
	if (root -> right) MirrorRecursively(root -> right);

	return;
}


// 非递归方式呢
void MirrorRecursively01(TreeNode *root) {
	stack<TreeNode *> stck;
	TreeNode *pNode = root;

	while (!stck.empty() && pNode) {
		while (pNode) {
			stck.push(root);
			if (root -> left || root -> right) {
				TreeNode *pTmp = root -> left;
				root -> left = root -> right;
				root -> right = pTmp;
			}
			root = root -> left;
		}

		pNode = stck.top();
		stck.pop();
		pNode = pNode -> right;
	}
}


int main() {
	return 0;
}
