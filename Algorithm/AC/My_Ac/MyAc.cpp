/**
* @file			MyAc.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月04日 星期六 13时53分02秒
*/


#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;

const int MAX_CHILD = 256;	

struct ACWord {
	unsigned int  len;
	char 		  *word;
	void 		  *info;

	ACWord() : len(0), word(NULL), info(NULL) {;}
};
#define WORD_STRING(node)		(node.word)
#define WORD_LEN(node)			(node.len)
#define WORD_INFO(node)			(node.info)

/*
 * @deatil trie数节点定义
 * */
struct ACNode {
	int 			count;
	ACNode 			*next[MAX_CHILD];
	ACNode 			*fail;
	bool 			exist;
	ACWord 			word;
	unsigned char   c;

	ACNode() : count(0), exist(false), fail(NULL) {
		for (int i = 0; i < MAX_CHILD; ++i) {
			next[i] = NULL;
		}
	}
};


bool AC_insert(ACNode *root, char *str) 
{
	if (root == NULL || str == NULL) 
		return false;

	int id  = 0;
	int len = 0;
	unsigned char *ptr = (unsigned char *)str;
	ACNode *pNode = root;

	while (*ptr) {
		id = *ptr;

		if (pNode -> next[id] == NULL) {
			pNode -> next[id] = new ACNode;
			pNode -> next[id] -> c = *ptr;
#ifdef DEBUG
			printf("pNode: %p, c: %c\n", pNode -> next[id], *ptr);
#endif
		}

		pNode = pNode -> next[id];
		pNode -> count ++;
		++ ptr; ++ len;
	}

	if (pNode -> exist == true)	{
#ifdef DEBUG
		cout << "the \"" << ptr << "\" is exist!" << endl;
#endif
		return true;
	}

	pNode -> exist = true;
	WORD_LEN(pNode -> word) = len;
	WORD_STRING(pNode -> word) = new char[len + 1];
	memcpy(WORD_STRING(pNode -> word), str, len);

	return true;
}

void AC_build_fail(ACNode *root)
{
	ACNode *pNode;
	queue<ACNode *> que;

	root -> fail = NULL;

	que.push(root);				// 入队

	while (!que.empty()) 		 // 队列判空 
	{		
		pNode = que.front();	// 获取队头元素
		que.pop();				// 出队

		for (int i = 0; i < MAX_CHILD; ++i) 
		{
			if (pNode -> next[i] != NULL) 
			{
				ACNode *pNodeFail = pNode -> fail;

				while (pNodeFail != NULL) {
					if (pNodeFail -> next[i] != NULL) {
#ifdef DEBUG
						printf("pNode: %p(%c) ---> fail: %p(%c)\n", 
								pNode -> next[i], pNode -> next[i] ->c, 
								pNodeFail -> next[i], pNodeFail -> next[i] ->c);
#endif
						pNode -> next[i] -> fail = pNodeFail -> next[i];
						break;
					}

					pNodeFail = pNodeFail -> fail;	
				}

				if (pNodeFail == NULL) {
#ifdef DEBUG
					printf("pNode: %p(%c) ---> root\n", pNode -> next[i], pNode -> next[i] -> c);
#endif
					pNode -> next[i] -> fail = root;
				}

				que.push(pNode -> next[i]);			
			}
		}
	}
}

bool AC_search(ACNode *root, char *str) 
{
	int id = 0;
	bool result = false;
	ACNode *pNode = root;
	unsigned char *ptr = (unsigned char *)str;

	while (*ptr) {
		id = *ptr;

		while (pNode -> next[id] == NULL && pNode != root) {
			pNode = pNode -> fail;
		}

		if (pNode -> next[id] != NULL) {
			pNode = pNode -> next[id];
		}

		ACNode *pTemp = pNode;

		while (pTemp != NULL) {
			if (pTemp -> exist == true) {
				result = true;
				cout << "匹配到 " << WORD_STRING(pTemp -> word) << endl;	
			}
			pTemp = pTemp -> fail;
		}

		ptr ++;
	}

	return result;
}



#if 0
#define TESTSTRING 	"shefghjkl;he dnsjvcndheshe"
int main()
{
	ACNode root;

	const int n = 3;
	char astring[128] = "\0";
	char str[][32] = {"she", "he", "shi"};
	strcpy(astring, TESTSTRING);

	for (int i = 0; i < n; i++){
		cout << ">>>>>>>>>>> AC_insert () : " << str[i] << endl;
		AC_insert(&root, str[i]);//执行插入结点
	}

	cout << ">>>>>>>>>>>>>> AC_build_fail() <<<<<<<<<<<<<<<<<<<\n"; 
	AC_build_fail(&root);

	cout << ">>>>>>>>>>>>>> AC_search(): " << astring << endl;; 
	AC_search(&root, astring);

	return 0;
}
#endif

#if 1
const int MAX_SIZE  = 1024;	

int main()
{
	cout << "\n" << endl;
	cout << "\t***************************************** " << endl;
	cout << "\t*\t\t\t\t\t*" << endl;
	cout << "\t*\t   本程序通过构建AC自动机   \t*" << endl;
	cout << "\t*    统计多模式串在目标串中的出现次数   *" << endl;
	cout << "\t*\t\t\t\t\t*" << endl;
	cout << "\t***************************************** " << endl;
	cout << endl << endl;

	ACNode *root=new ACNode;
	int n = 0, count1 = 0;
	cout << "--请输入单词子串数量:" ;
	cin >> n;
	char **str=new char*[n];
	char *astring = new char[MAX_SIZE];

	cout << "--请逐个输入单词子串（子串字母长度应少于"<<MAX_SIZE <<"）:"<< endl;
	for (int i = 0; i < n; i++){
		str[i] = new char[MAX_SIZE];
		cin >> str[i];
	}

	for (int i = 0; i < n; i++){
		AC_insert(root, str[i]);
	}

	AC_build_fail(root);

	cout << "--请输入目标串（字母长度应少于"<<MAX_SIZE<<"）:" << endl;
	cin >> astring;
	count1 = AC_search(root, astring);

	return 0;
}


#endif
