/**
* @file			36_Convert.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月16日 星期四 21时05分16秒
*/

#include <iostream>
#include "BinTree.h"
using namespace std;


void ConvertNode(TreeNode *root, TreeNode **pLastNodeInList, TreeNode **pHead) {
	if (root) {
		if (root -> left) ConvertNode(root -> left, pLastNodeInList, pHead);
	
		TreeNode *pCurNode = root;
		pCurNode -> left = *pLastNodeInList;
		if (*pLastNodeInList) (*pLastNodeInList) -> right = pCurNode;
		else *pHead = pCurNode;
		*pLastNodeInList = pCurNode;

		if (root -> right) ConvertNode(root -> right, pLastNodeInList, pHead);
	}
}


TreeNode *convert(TreeNode *root) {
	TreeNode *pLastNodeInList = NULL;	
	TreeNode *pHead = NULL;	
	ConvertNode(root, &pLastNodeInList, &pHead);

	return pHead;
}

int main() {
	return 0;
}
