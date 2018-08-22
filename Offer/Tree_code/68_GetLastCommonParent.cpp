/**
* @file			68_GetLastCommonParent.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 12时43分49秒
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include "BinTree.h"
using namespace std;

static bool GetNodePath(TreeNode *root, TreeNode *pNode, vector<TreeNode *> &path) {
	if (root == NULL || pNode == NULL)	return false;

	if (root == pNode) {
		path.push_back(root);
		return true;
	}
	path.push_back(root);

	bool found = false;
	found = GetNodePath(root -> left, pNode, path);
	if (!found)	found = GetNodePath(root -> right, pNode, path);

	if (!found)	path.pop_back();

	return found;
} 

static TreeNode *GetLastCommonNode(vector<TreeNode *> &path1, vector<TreeNode *> &path2) {
	int size1 = path1.size(), size2 = path2.size();
	int len = min(size1, size2);
	TreeNode *commNode = NULL;
	for (int i = 0; i < len; i++) {
		if (path1[i] != path2[i]) {
			commNode = path2[i - 1];	
		}
	}
	return commNode;
}

TreeNode *GetLastCommonParent(TreeNode *root, TreeNode *pNode1, TreeNode *pNode2) {
	if (!root || !pNode1 || !pNode2) return NULL;

	vector<TreeNode *> path1, path2;
	GetNodePath(root, pNode1, path1);
	GetNodePath(root, pNode2, path2);
	return GetLastCommonNode(path1, path2);	
}

int main() {
	return 0;
}
