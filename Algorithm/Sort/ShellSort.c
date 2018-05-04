/**
* @file			ShellSort.c
* @brief		希尔排序
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月01日 星期二 15时52分57秒
*/

#include "Common.h"

/*
 * 	初始值  9  1  5  8  3  7  4  6  2
 * 	        |-----------|-----------|
 * 	           |-----------|
 * 	              |-----------|
 * 	                 |-----------|
 *  第一趟  2  1  4  6  3  7  5  8  9  （增值为len/3+1=4）
 *          |-----|-----|-----|-----|
 *             |-----|-----|-----|
 *  第二趟  2  1  3  6  4  7  5  8  9   （增值为4/3+1=2）
 *          |--|--|--|--|--|--|--|--|
 *  第三趟  1  2  3  4  5  6  7  8  9	（增值为2/3+1=1）
 *
 *  对于最好的增量序列至今未找到
 *  但当增量序列为 dlta[k] = 2^(t-k+1)-1 ( 0 <= k <= t <= log2[n+1] )时，可以获得不错的效果
 * */
void ShellSort(SqList *L)
{
	int 	i, j;
	int 	increment = L->length;

	do {
		increment = increment / 3 + 1;					/* 增量序列 */

		for (i = increment + 1; i < L->length; i++) { 	/* 需将L->r[i]插入有序增量列表 */
			L->r[0] = L->r[i];

			for (j = i - increment; 
					j > 0 && L->r[0] < L->r[j]; 
					j -= increment) 
			{
				L->r[j + increment] = L->r[j];			/* 记录后移 查找插入位置 */
			}

			L->r[j + increment] = L->r[0];
		}
	} while(increment > 1);

	return;
}
