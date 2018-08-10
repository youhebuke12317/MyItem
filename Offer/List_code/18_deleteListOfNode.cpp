/**
* @file			18_deleteListOfNode.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 07时18分26秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

/* O(1)时间内删除链表制定节点 */
void DeleteListOfNode(ListNode **head, ListNode *pdelNode) {
	if (head == NULL || pdelNode == NULL) return;

	// 待删除节点不是尾节点
	if (pdelNode -> next != NULL) {
		ListNode *pNode = pdelNode -> next;
		pdelNode -> val = pNode -> val;
		pdelNode -> next = pNode -> next;
		delete pNode;
	}
	// 链表中只有一个节点，待删除节点就是这一个节点
	else if (*head == pdelNode) {
		delete pdelNode;
		*head = NULL;
	}
	// 链表中有多个节点，待删除节点是尾节点
	else {
		ListNode *pNode = *head;
		while (pNode -> next != pdelNode) {
			pNode = pNode -> next;
		}
		pNode -> next = NULL;
		delete pdelNode;
	} 

	return;
}


/* 去除排序链表中重复节点 */
ListNode * RemoveDuplication(ListNode *head) {
	if (head == NULL) return head;
	ListNode *pNode = head;

	while (pNode) {
		while (pNode -> next && pNode -> val == pNode -> next -> val) {
			ListNode * pTemp = pNode -> next;
			pNode -> next = pNode -> next -> next;
			delete pTemp;
		}
		pNode = pNode -> next;
	}
	return head;
}

/* 删除排序链表中重复节点 */
ListNode * DeleteDuplication(ListNode **head) {
	if( *head == NULL ) return *head;
	ListNode *pPreNode = NULL;   // 指向前面最晚访问过的不重复结点
	ListNode *pCurNode = *head;  // 指向当前处理的结点
	ListNode *pAftNode = NULL;   // 指向当前处理结点后面结点
	while( pCurNode ) {
		if (pCurNode -> next && pCurNode -> next -> val == pCurNode -> val) {
			pAftNode = pCurNode -> next;
			while (pAftNode && pAftNode -> next && pAftNode -> next -> val == pAftNode -> val) {
				pAftNode = pAftNode -> next;
			}

			if (pCurNode == *head) *head = pAftNode -> next;
			else pPreNode -> next = pAftNode -> next;

			ListNode *pTemp = pCurNode;
			while (pTemp && pTemp != pAftNode) {
				ListNode *q = pTemp -> next;
				delete pTemp;
				pTemp = q;
			}

			pCurNode = pAftNode -> next;
		}
		else {
			pPreNode = pCurNode;
			pCurNode = pCurNode -> next;
		}
	}
	return *head;
}

void output(ListNode *head) {
	ListNode *pNode = head;
	printf("[");
	while (pNode) {
		printf("%d ", pNode -> val);
		pNode = pNode -> next;
	}
	printf("]\n");
}

int main()
{
	ListNode *head = NULL, *p;
	int num[10] = {1, 1, 1, 3, 5, 6, 9, 9, 9, 9};
	for (int i = 0; i < 10; i++) {
		ListNode *pNode = new ListNode(num[i]);
		if (head == NULL) head = pNode, p = pNode;
		else p->next = pNode, p = pNode;
	}

	output(head);
	DeleteDuplication(&head);
	output(head);
}
