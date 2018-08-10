/**
* @file			25_MergerList.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月08日 星期三 10时37分33秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

ListNode *MergerList(ListNode *head1, ListNode *head2) {
	ListNode *pNewHead = NULL;
	ListNode *pNode1 = head1;
	ListNode *pNode2 = head2;
	ListNode *pNewNode = NULL;

	if (!pNode1 && !pNode2) pNewHead = NULL;

	while (pNode1 && pNode2) {
		if (pNode1 -> val > pNode2 -> val) {
			if (!pNewNode) pNewHead = pNode2, pNewNode = pNode2;
			else pNewNode -> next = pNode2, pNewNode = pNode2;
			pNode2 = pNode2 -> next;

		}
		else {
			if (!pNewNode) pNewHead = pNode1, pNewNode = pNode1;
			else pNewNode -> next = pNode1, pNewNode = pNode1;
			pNode1 = pNode1 -> next;
		}
	}

	if (!pNode1) pNewNode -> next = pNode2;
	if (!pNode2) pNewNode -> next = pNode1;

	return pNewHead;
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
	int num[10] = {1, 3, 5, 7, 9, 11, 13, 15, 19, 20};
	int num1[10] = {2, 4, 6, 8, 10, 12, 14, 16, 17, 18};

	ListNode *head = NULL, *head1 = NULL, *p, *p1;
	for (int i = 0; i < 10; i++) {
		ListNode *pNode = new ListNode(num[i]);
		if (head == NULL) head = pNode, p = pNode;
		else p->next = pNode, p = pNode;
		

		ListNode *pNode1 = new ListNode(num1[i]);
		if (head1 == NULL) head1 = pNode1, p1 = pNode1;
		else p1->next = pNode1, p1 = pNode1;
	}

	output(head);
	output(head1);
	ListNode *newhead = MergerList(head, head1);
	output(newhead);
}
