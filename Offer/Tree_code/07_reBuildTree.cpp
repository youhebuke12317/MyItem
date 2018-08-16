/**
* @file			07_reBuildTree.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月11日 星期六 11时33分21秒
*/

#include <iostream>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include "BinTree.h"
using namespace std;


static TreeNode *__ReBuildTree(int *startPre, int *endPre, int *startIn, int *endIn) {
	// 创建节点
	int rootValue = startPre[0];
	TreeNode *root = new TreeNode(rootValue);

	// 终结条件与异常抛出
	if (startPre == endPre) {
		if (startIn == endIn && *startPre == *startIn) return root;
		else THROW_EXCEPTION("Invalid input!");
	}

	// 查找中序遍历中节点位置
	int *rootIn = startIn;
	while (rootIn < endIn && *rootIn != rootValue) ++rootIn;

	// 异常抛出
	if (rootIn == endIn && *rootIn != rootValue) THROW_EXCEPTION("Invalid input!");

	// 递归调用
	int leftLen = rootIn - startIn;
	if (leftLen > 0) 
		root -> left = __ReBuildTree(startPre, startPre + leftLen, startIn, rootIn - 1);
	else if (leftLen < (endPre - startPre)) 
		root -> right = __ReBuildTree(startPre + leftLen + 1, endPre, rootIn + 1, endIn);

	return root;
}

TreeNode *ReBuildTree(int *preorder, int *inorder, int len) {
	if (!preorder || !inorder || len < 0) return NULL;
	
	return __ReBuildTree(preorder, preorder + len - 1, inorder, inorder + len - 1); 
}


int main() {
	return 0;
}
