/**
* @file			QuitSort.c
* @brief		快速排序
* @detils		通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均
* 				比另一部分记录的关键字小 则可分别对这两部分记录继续进行排序，已达到
* 				整个序列有序的目的
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月03日 星期四 19时35分26秒
*/

#include "Common.h"

static void QSort(SqList *, int, int);

/*
 * 初始数据：50 10 90 30 70 40 80 60 20
 * */
void QuitSort(SqList *L)
{
	QSort(L, 1, L->length);	
}


static void QSort(SqList *L, int low, int high)
{
	int 	pivot;
}

