/**
* @file			SelectSort.c
* @brief		简单选择排序
* @detils		通过 n-i 次关键字比较 从 n-i+1 个记录中选出关键字最小的记录 并和 i 个记录交换之
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月01日 星期二 15时23分17秒
*/

#include "Common.h"

void SelectSort(SqList *L)
{
	int 	i, j, min;

	for (i = 1; i < L->length; i++) {
		min = i;			/* 将当前下标定义为最小值下标 */

		for (j = i + 1; j < L->length; j++) {
			if (L->r[min] > L->r[j]) {
				min = j;		/* 记录每次外层循环的最小值下标 */
			}
		}

		if (min != i) {			/* 如果最小值下标不是本次循环开始的下标(i) */
			Swap(L, i, min);	/* 交换 */
		}
	}
	return ;
}
