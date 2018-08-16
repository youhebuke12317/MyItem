/**
* @file			31-1_printFromTopBottom.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 17时11分39秒
*/

#include <iostream>
#include <queue>
#include "BinTree.h"
using namespace std;

void printFromTopBottom(TreeNode *root) {
	queue<TreeNode *> queue;
	if (root) queue.push(root);

	while (!queue.empty()) {
		TreeNode *pNode = queue.front();
		queue.pop();
		cout << pNode -> val << " ";
		if (pNode -> left) queue.push(pNode -> left);
		if (pNode -> right) queue.push(pNode -> right);
	} 
	cout << endl;
	return;
}

int main() {
	return 0;
}
