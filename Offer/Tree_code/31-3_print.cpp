/**
* @file			31-3_print.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月16日 星期四 18时50分12秒
*/

#include <iostream>
#include <stack>
#include "BinTree.h"
using namespace std;

void printNode (TreeNode *root) {
	if (!root)	return;
	stack<TreeNode *> stack[2];
	int curr = 0, next = 1;

	stack[curr].push(root);
	while (!stack[0].empty() || !stack[1].empty()) {
		TreeNode *pNode = stack[curr].top();
		stack[curr].pop();

		cout << pNode -> val << " ";

		if (curr == 0) {
			if (pNode -> left) stack[next].push(pNode -> left);
			if (pNode -> right) stack[next].push(pNode -> right);
		} 
		else {
			if (pNode -> right) stack[next].push(pNode -> right);
			if (pNode -> left) stack[next].push(pNode -> left);
		}

		if (stack[curr].empty()) {
			cout << endl;
			curr = 1 - curr;
			next = 1 - next;
		}
	}
}

int main() {
	return 0;
}
