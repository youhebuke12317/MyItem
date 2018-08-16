/**
* @file			08_GetNext.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 09时47分28秒
*/

#include <iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;

	TreeNode (int data = 0) : val(data), left(NULL), right(NULL) {}
};

TreeNode *__GetNextOfInorder(TreeNode *pNode) {
	if (pNode -> right) {
		TreeNode *pTemp = pNode -> right;
		while (pTemp -> left) pTemp = pTemp -> left;
		return pTemp;
	}

	TreeNode *pCur = pNode;
	TreeNode *pParent = pNode -> parent;
	while (pParent && pCur == pParent -> right) {
		pCur = pParent;
		pParent = pParent -> parent;
	}
	return pParent;
}

TreeNode *GetNextOfInorder(TreeNode *pNode) {
	if (pNode == NULL)  return NULL; 
	return __GetNextOfInorder(pNode);
}


int main() {
	return 0;
}
