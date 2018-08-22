/**
* @file			37_serializeTree.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 10时47分10秒
*/

#include <iostream>
#include <cstdio>
#include "BinTree.h"
using namespace std;

#define NODE_NULL	"$, "

void __serializeTree(TreeNode *root) {
	if (!root) printf(NODE_NULL);
	printf("%d, ", root -> val);
	__serializeTree(root -> left);
	__serializeTree(root -> right);
}

void serializeTree(TreeNode *root) {
	__serializeTree(root);
	printf("\n");
}

int main() {
	return 0;
}
