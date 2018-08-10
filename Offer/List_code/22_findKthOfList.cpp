/**
* @file			22_findKthOfList.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月08日 星期三 09时38分02秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

ListNode * FindKthOdList(ListNode *head, int k) {
	if (head == NULL || k <= 0) return NULL;
	ListNode *pNode = head;
	int len = 0;
	while (pNode) pNode = pNode -> next, ++len;
	if (k > len) return NULL;

	pNode = head;
	ListNode *pPreNode = head;
	for (int i = 0; i < len - k + 1; i++)
		pPreNode = pPreNode -> next;	

	while (pPreNode) {
		pPreNode = pPreNode -> next;
		pNode = pNode -> next;
	}

	return pNode;
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
	ListNode *pNode = FindKthOdList(head, 10);
	output(head);
	if (pNode) printf("%d\n", pNode -> val);
	else printf("FindKthOdList func return NULL\n");
}
