/**
* @file			52_CommNodeOfList.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月08日 星期三 23时58分58秒
*/

#include <iostream>
#include <cstdio>
#include "ListNode.h"
using namespace std;

int GetLenOfList(ListNode *head) {
	int len = 0;
	ListNode *pNode = head;
	while (pNode) {
		pNode = pNode -> next;
		len ++;
	}
	return len;
}

ListNode * CommNodeOfList(ListNode *head1, ListNode *head2) {
	int len1, len2, len;
	ListNode *pNode = NULL;
	ListNode *pNode1 = head1;
	ListNode *pNode2 = head2;

	len1 = GetLenOfList(head1);
	len2 = GetLenOfList(head2);
	if (len1 - len2 < 0) {
		for (int i = 0; i < len2 - len1; i++) 
			pNode2 = pNode2 -> next;
	}
	else {
		for (int i = 0; i < len1 - len2; i++) 
			pNode1 = pNode1 -> next;
	}
	
	while (pNode1 && pNode2 && pNode1 != pNode2) {
		pNode1 = pNode1 -> next;
		pNode2 = pNode2 -> next;
	}
	
	if (pNode1 == pNode2) pNode = pNode1;
	
	return pNode;
}
int main()
{
	// 牛客网通过
	return 0;
}
