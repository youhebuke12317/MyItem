/**
* @file			tree_order.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月10日 星期五 12时48分27秒
*/

#include <iostream>
#include <stack>
#include <cstdio> 
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
};


// 递归方式的前序遍历
void PreOrderOfTree_01(TreeNode *root) {
	if (root) {
		printf("%d ", root -> val);
		PreOrderOfTree_01(root -> left);
		PreOrderOfTree_01(root -> right);
	}
}

// 递归方式的中序遍历
void InOrderOfTree_01(TreeNode *root) {
	if (root) {
		InOrderOfTree_01(root -> left);
		printf("%d ", root -> val);
		InOrderOfTree_01(root -> right);
	}
}

// 递归方式的后序遍历
void PostOrderOfTree_01(TreeNode *root) {
	if (root) {
		PostOrderOfTree_01(root -> left);
		PostOrderOfTree_01(root -> right);
		printf("%d ", root -> val);
	}
}

/*
 * 非递归方式的前序遍历与中序遍历过程一样
 * 		都需要一个辅助栈
 * 		前序遍历是在入队时输出
 * 		中序遍历是在出队时输出
 * */
// 非递归方式的前序遍历
void PreOrderOfTree_02(TreeNode *root) {
	TreeNode *pNode = root;
	stack<TreeNode *>	stck;

	while (!stck.empty() && pNode) {
		while (pNode) {
			stck.push(pNode);
			printf("%d ", pNode -> val);
			pNode = pNode -> left;
		}

		pNode = stck.top();
		stck.pop();
		pNode = pNode -> right;
	}
}

// 非递归方式的中序遍历
void InOrderOfTree_02(TreeNode *root) {
	TreeNode *pNode = root;
	stack<TreeNode *>   stck;

	while (!stck.empty() && pNode) {
		while (pNode) {
			stck.push(pNode);
			pNode = pNode -> left;
		}

		pNode = stck.top();
		stck.pop();
		printf("%d ", pNode -> val);
		pNode = pNode -> right;
	}
}


#define CHILD_IS_NULL(node)						\
	((!node -> left) && (!node -> right))
#define CHILD_IS_VISITED(node, child)  			\
	(child && (child == node -> left || child == node -> right))

// 非递归方式的后序遍历
void PostOrderOfTree_02(TreeNode *root) {
	stack<TreeNode *> stck;
	TreeNode *pCurNode = NULL;
	TreeNode *pPreNode = NULL;
	stck.push(root);

	while (!stck.empty()) {
		pCurNode = stck.top();
		if ( CHILD_IS_NULL(pCurNode) || CHILD_IS_VISITED(pCurNode, pPreNode) ) {
			printf("%d ", pCurNode -> val);	// 如果当前结点没有孩子结点或者孩子节点都已被访问过 
			stck.pop();
			pPreNode = pCurNode;
		}
		else {
			if (pCurNode -> left)  stck.push(pCurNode -> left);
			if (pCurNode -> right) stck.push(pCurNode -> right);
		}
	}
}

int main()
{
	return 0;
}
