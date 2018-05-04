/**
* @file			InsertSort.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月01日 星期二 15时33分33秒
*/

#include "Common.h"

void InsertSort(SqList *L)
{
	int 	i, j;

	for (i = 2; i < L->length; i++) {

		if (L->r[i] < L->r[i - 1]) {

			L->r[0] = L->r[i];			/* 设置哨兵 */	

			for (j = i - 1; L->r[j] > L->r[0]; j--) {
				L->r[j + 1] = L->r[j];	/* 记录后移 */
			}

			L->r[j + 1] = L->r[0];		/* 插入到正确的位置 */
		}
	}
	return ;
}
