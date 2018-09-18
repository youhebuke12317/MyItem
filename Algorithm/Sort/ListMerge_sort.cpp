/*************************************************************************
    > File Name: ListMerge_sort.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 一  9/17 08:21:03 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v): value(v), next(NULL) {}
};

ListNode *mergeSortedList(ListNode *L1, ListNode *L2) {
	ListNode dummy(-1); dummy -> next = L1;
	ListNode *p1 = &dummy, p2 = L2;

	while (p1 -> next && p2) {
		if (p1 -> next -> val >= p2 -> val) {
			L2 = p2 -> next;
			p2 -> next = p1 -> next;
			p1 -> next = p2;
			p1 = p2;
			p2 = L2;
		}
		else p1 = p1 -> next;
	}
	if (!(p1 -> next)) p1 -> next = p2;

	return dummy.next;
}

ListNode *ListMergeSort(ListNode *head) {
	if (!head || !(head -> next)) return head;

	ListNode *slow = head, *fast = head;
	while (fast -> next && fast -> next -> next) {
		fast = fast -> next -> next;
		slow = slow -> next;
	}

	ListNode *leftHead = head, *rightHead = slow -> next;
	slow -> next = NULL;

	leftHead = ListMergeSort(leftHead);
	rightHead = ListMergeSort(rightHead);

	return mergeSortedList(leftHead, rightHead);
}
