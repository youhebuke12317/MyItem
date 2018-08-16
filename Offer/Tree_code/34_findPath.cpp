/**
* @file			34_findPath.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月16日 星期四 20时20分29秒
*/

#include <iostream>
#include <vector>
#include "BinTree.h"
using namespace std;

void findPahtCore(TreeNode *root, int sum, vector<int> &path, int cursum) {
	cursum += root -> val;
	path.push_back(root -> val);

	if (cursum == sum && !(root -> left) && !(root -> right)) {
		cout << "A path is found: ";
		vector<int>::iterator iter = path.begin();
		for (; iter != path.end(); ++iter) cout << *iter << "\t";
		cout << endl;
	}

	if (root -> left) findPahtCore(root -> left, sum, path, cursum);
	if (root -> right) findPahtCore(root -> right, sum, path, cursum);

	path.pop_back();
}

void findPath(TreeNode *root, int sum) {
	if (root == NULL)	return;
	vector<int> path;
	findPahtCore(root, sum, path, 0);
}

int main() {
	return 0;
}
