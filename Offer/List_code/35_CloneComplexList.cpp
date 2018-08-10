/**
* @file			35_CloneList.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月08日 星期三 19时25分40秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

void CloneNodes(ComplexListNode *head) {
	ComplexListNode *pNode = head;
	while (pNode) {
		ComplexListNode *pNew = new ComplexListNode(pNode -> val);
		pNew -> next = pNode -> next;
		pNode -> next = pNew;
		pNode = pNew -> next;
	}
	return;
}

void ConnectSilbNodes(ComplexListNode *head) {
	ComplexListNode *pNode = head;
	while (pNode) {
		ComplexListNode *pCloned = pNode -> next;
		if (pNode -> sibl) pCloned -> sibl = pNode -> sibl -> next;
		pNode = pCloned -> next;
	}
	return;
}

ComplexListNode *ReConnectNodes(ComplexListNode *head) {
	ComplexListNode *pNode = head;
	ComplexListNode *pNewHead = NULL;
	ComplexListNode *pCloned = NULL;

	if (pNode) {
		pCloned = pNewHead = pNode -> next;
		pNode -> next = pCloned -> next;
		pNode = pCloned -> next;
	}
	while (pNode) {
		pCloned -> next = pNode -> next;
		pCloned = pCloned -> next;
		pNode -> next = pCloned -> next;
		pNode = pNode -> next;
	}
	return pNewHead;
}

ComplexListNode* CloneList(ComplexListNode *head) {
	if (head == NULL) return NULL;	
	CloneNodes(head);
	ConnectSilbNodes(head);
	return ReConnectNodes(head);
}

int main() {
	return 0;
}
