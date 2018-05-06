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
static int Partition(SqList *, int, int);

/*
 * 初始数据：50 10 90 30 70 40 80 60 20
 *						 
 * 第一趟：  20 10 40 30 50 70 80 60 90
 *						 |
 * 第二趟：	 10 20 40 30 50 60 70 80 90
 *			    |        |     |
 * 第三趟：	 10 20 30 40 50 60 70 80 90
 *				|	  |  |     |  |
 * 第四趟：  10 20 30 40 50 60 70 80 90
 * */

void QuitSort(SqList *L)
{
	QSort(L, 1, L->length);	
}

// 对顺序表 L 中的子序列 L->r[low..high] 作快速排序
static void QSort(SqList *L, int low, int high)
{
	int 	pivot;

	if (low < high) {
			
		pivot = Partition(L, low, high);	/* 将 L->r[low..high] 一份为二 */
											/* 算出枢轴值 pivot */
		QSort(L, low, pivot - 1);

		QSort(L, pivot + 1, high);
	}

	return ;
}

// 交换顺序表 L 中子表的记录，使枢轴记录到位，并返回其所在位置
// 此时在它之前（后）的记录均不大（小）于它
static int Partition(SqList *L, int low, int high)
{
	int		pivotkey;

	// 1 优化选取枢轴
	{
		int	m = low + (high - low) / 2;
		if (L->r[low] > L->r[high])	Swap(L, low, high);		/* 交换左右端数据 保证左端较小 */
		if (L->r[m] > L->r[high])	Swap(L, m, high);		/* 交换中间与右端数据 保证中间较小 */
		if (L->r[m] > L->r[low])	Swap(L, m, low);		/* 交换中间与左端数据 保证左端较小 */
		/* 此时 L.r[low]已经是整个序列中左右三个关键字的中间值 */
	}

	pivotkey = L->r[low];		/* 用子表的第一个记录作枢轴记录 */

	// 2 优化不必要的交换
	{
		L -> r[0] = pivotkey;
	}

	while (low < high) {
		while (low < high && L->r[high] >= pivotkey)	high--;

		// Swap(L, low, high);
		L -> r[low] = L -> r[high];		// 2 优化不必要的交换

		while (low < high && L->r[low] <= pivotkey)		low++;

		// Swap(L, low, high);
		L -> r[high] = L -> r[low];		// 2 优化不必要的交换
	}

	L -> r[low] = L -> r[0];

	return low;
}
