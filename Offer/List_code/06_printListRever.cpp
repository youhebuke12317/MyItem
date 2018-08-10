/**
* @file			06_printListRever.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 07时03分59秒
*/

#include <iostream>
#include <stack>
#include <cstdio>
#include "ListNode.h"
using namespace std;


void printListFromTailToHead(ListNode *head)
{
	stack<ListNode *>	stck;

	ListNode *pNode = head;

	while (pNode) {
		stck.push(pNode);
		pNode = pNode -> next;
	}

	while (!stck.empty()) {
		pNode = stck.top();
		cout << pNode->val << endl;
		stck.pop();
	}
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
	int num[10] = {1, 1, 3, 3, 5, 6, 7, 8, 9, 10};
	for (int i = 0; i < 10; i++) {
		ListNode *pNode = new ListNode(num[i]);
		if (head == NULL) head = pNode, p = pNode;
		else p->next = pNode, p = pNode;
	}

	output(head);
	printListFromTailToHead(head);
	output(head);
}
