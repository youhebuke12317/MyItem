/**
* @file			BubbleSort.c
* @brief		冒泡排序
* @detils		两辆比较相邻记录的关键字 如果反序则交换 知道没有反序记录为止
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月01日 星期二 14时52分46秒
*/

#include "Common.h"

/*
 * 该算法效率低 严格上也不属于冒泡排序
 *
 * 每一个循环排序好的一个数字，但是对后续的排序没有任何帮助
 * */
void BubbleSort_0(SqList *L)
{
	int i, j;

	for (i = 1; i < L->length; i++) {
		for (j = i + 1; j < L->length; j++) {
			if (L->r[i] > L->r[j]) {
				Swap(L, i, j);		/* 交换 L->r[i] 与 L->r[j] 的值 */
			}
		}		
	}
	return ;
}


void BubbleSort(SqList *L) 
{
	int i, j;

	for (i = 1; i < L->length; i++) {	
		for (j = L->length; j >= i; j--) {		/* 注意 j 是从后往前循环 */
			if (L->r[j] > L->r[j + 1]) {		/* 若前者大于后者 */
				Swap(L, j, j + 1);
			}
		}
	}
	return ;
}

#define  SORT_FALSE		0
#define  SORT_TRUE		1

void BubbleSort_2(SqList *L)
{
	int 	i, j;
	char 	flag = SORT_FALSE;		/* flag 用来作为标记 */

	for (i = 1; i < L->length && flag == SORT_TRUE; i++) {	
		flag = SORT_FALSE;			/* 每次外循环的初始值为SORT_FALSE */
		for (j = L->length; j >= i; j--) {
			if (L->r[j] > L->r[j + 1]) {
				Swap(L, j, j + 1);
				flag = SORT_TRUE;	/* 如果有数据交换 SORT_FALSE -> SORT_TRUE */
			}
		}
	}
	return ;
}
