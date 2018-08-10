/**
* @file			ListNode.h
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月07日 星期二 07时18分54秒
*/

#pragma once

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

struct ComplexListNode {
	int val;
	struct ComplexListNode *next;
	struct ComplexListNode *sibl;
	ComplexListNode(int x) :
		val(x), next(NULL), sibl(NULL) {
	}
};
