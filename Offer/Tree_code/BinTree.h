/**
* @file			BinTree.h
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月14日 星期二 08时36分03秒
*/


// gcc抛出异常
#define THROW_EXCEPTION(x)				\
	do {								\
		logic_error ex(x);				\
		throw exception(ex);			\
	} while (0)

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode (int data = 0) : val(data), left(NULL), right(NULL) {}
};
