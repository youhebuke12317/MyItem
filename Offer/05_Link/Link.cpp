/**
* @file			Link.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年04月09日 星期一 20时07分32秒
*/

#include <iostream>
using namespace std;

struct ListNode {
	int 			value;
	struct ListNode	*next;
};

/*
 * @detail 往链尾插入一个节点
 * */
int AddToTail(struct ListNode **pHead, int value)
{
	struct ListNode	*pNew = new ListNode();

	pNew -> value = value;
	pNew -> next  = NULL;

	if (*pHead == NULL) {
		*pHead = pNew;
	} 
	else {
		struct ListNode *pNode = *pHead; 
		while (pNode -> next != NULL) {
			pNode = pNode -> next;
		}
		pNode -> next = pNew;
	}

	return 0;
}

/*
 * @detail 在链表中找到第一个含有某值的节点并删除
 * */
int RemoveNode(struct ListNode **pHead, int value)
{
	if (pHead == NULL || *pHead == NULL)	return -1;

	ListNode *pDel  = *pHead;
	ListNode *pNode = *pHead;

	if (pNode -> value == value) {
		pDel   = pNode;
		*pHead = pNode -> next;
	}
	else {
		while (pNode -> next != NULL) {
			// 单向链表时 需要找到删除节点的前一个节点
			if (pNode -> next -> value == value) 	break;		
			pNode = pNode -> next;
		}
		
		if (pNode -> next != NULL && pNode -> next -> value == value) {
			pDel = pNode -> next;
			pNode -> next = pNode -> next -> next;
		} 
	} 

	if (pDel != NULL) {
		delete	pDel;
		pDel = NULL;
	}

	return 0;
}

