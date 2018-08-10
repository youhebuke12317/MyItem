/**
* @file			23_looplist.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月09日 星期四 08时52分43秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

// 查找链表是否有环 --- ERROR
ListNode *isloopOfList(ListNode *head) {
	if (head == NULL) return NULL;

	ListNode *pNodeFast = head;
	ListNode *pNodeSlow = head;
	while (pNodeFast && pNodeFast -> next && pNodeFast -> next -> next) {
		if (pNodeFast != head && pNodeFast == pNodeSlow) pNodeFast;
		pNodeFast = pNodeFast -> next -> next;
		pNodeSlow = pNodeSlow -> next;
	}

	return NULL;
}

ListNode *MeetingNode(ListNode *head) {
	if (!head) return NULL;

	ListNode *pSlow = head -> next;
	if (!pSlow) return NULL;
	ListNode *pFast = pSlow -> next;
	while (pFast && pSlow) {
		if (pFast == pSlow) return pFast;
		pSlow = pSlow -> next;
		pFast = pFast -> next;
		if (pFast) pFast = pFast -> next;
	}
	return NULL;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	ListNode *pNode = isloopOfList(pHead);
	if (!pNode) return NULL;

	int len = 1;
	ListNode *pTmp = pNode -> next;
	while (pTmp != pNode) len++, pTmp = pTmp -> next;

	pTmp = pHead;
	ListNode *pTmp2 = pHead;
	for (int i = 0; i < len; i++) {
		pTmp = pTmp -> next;
	}

	while (pTmp != pTmp2) {
		pTmp = pTmp -> next;
		pTmp2 = pTmp2 -> next;
	} 

	return pTmp;
}

int main()
{
	return 0;
}
