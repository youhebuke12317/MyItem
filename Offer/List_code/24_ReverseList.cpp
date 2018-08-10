/**
* @file			24_ReverseList.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月08日 星期三 09时51分20秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

void ReverseList_Error_Gai(ListNode **head) {
	if (head == NULL || *head == NULL 
			|| (*head) -> next == NULL)	return ;

	int index = 0;
	ListNode *pNode = *head;
	ListNode *pTemp = (*head) -> next;
	ListNode *pNext = (*head) -> next -> next;
	while (pNext) {
		pTemp -> next = pNode;
		if (pNode == *head) pNode -> next = NULL;
		pNode = pTemp;
		pTemp = pNext;
		pNext = pTemp -> next;
	}
	pTemp -> next = pNode;
	if (pNode == *head) pNode -> next = NULL;
	*head = pTemp;
	return ;
}

ListNode * ReverseList(ListNode *head) {
	ListNode *pReHead = NULL;
	ListNode *pNode = head;
	ListNode *pPre = NULL;
	while (pNode) {
		ListNode *pNext = pNode -> next;
		if (pNext == NULL) pReHead = pNode;
		pNode -> next = pPre;
		pPre = pNode;
		pNode = pNext;
	}
	return pReHead;
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
	// ListNode *pNode = ReverseList(head);
	ReverseList_Error_Gai(&head);
	output(head);
}
