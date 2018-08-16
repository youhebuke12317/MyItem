/**
* @file			31-2_printTreeNode.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月16日 星期四 18时37分14秒
*/

#include <iostream>
#include <queue>
#include "BinTree.h"
using namespace std;

void printTreeNode(TreeNode *root) {
	queue<TreeNode *>	queue;
	int nextLevel = 0;
	int toBeprint = 1;
	if (root) queue.push(root);
	while (!queue.empty()) {
		TreeNode *pNode = queue.front();
		cout << pNode -> val << " ";
		if (pNode -> left)  queue.push(pNode -> left),  ++ nextLevel;
		if (pNode -> right) queue.push(pNode -> right), ++ nextLevel;

		queue.pop();
		-- toBeprint;
		if (!toBeprint) {
			cout << endl;
			toBeprint = nextLevel;	// 上一层节点个个数
			nextLevel = 0;			
		}
	}
	return;
}

int main() {
	return 0;
}
