/**
* @file			MergeSort.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月02日 星期三 21时10分36秒
*/

#include "Common.h"

static void MSort(int *, int *, int, int);
static void Merge(int *, int *, int, int, int);
static void MergePass(int *, int *, int, int);


void MergeSort(SqList *L)
{
	MSort(L->r, L->r, 1, L->length);
}

void MergeSort2(SqList *L)
{
	int		k = 1;
	int 	TR[MAXSIZE + 1];

	while (k < L->length) {

		MergePass(L->r, TR, k, L->length);
		k = 2 * k;
		MergePass(TR, L->r, k, L->length);

		k = 2 * k;
	}

	return ;
}

/* 将 SR[] 中相邻长度为 s 的子序列两两归并到 TR[] */
static void MergePass(int *SR, int *TR, int s, int n)
{
	int 	i = 1, j;

	while (i <= n - 2*s + 1) {

		Merge(SR, TR, i, i + s - 1, i + 2*s - 1);	/* 两两归并 */

		i = i + 2*s;
	}

	if (i < n - s + 1) {				/* 归并最后两个序列 */
		Merge(SR, TR, i, i + s -1, n);
	}

	else {
		for (j = i; j <= n; j++) 		/* 若最后只剩下单个子序列 */
			TR[j] = SR[j];
	}

	return ;
}

static void MSort(int *SR, int *TR1, int s, int t)
{
	int 	m;
	int 	TR2[MAXSIZE + 1];

	if (s == t)	{
		TR1[s] = SR[s];				/* 递归之后将数据拷贝到TR1中 */
	}

	else {
		m = (s + t) / 2;

		MSort(SR, TR2, s, m);		/* 将 SR[s..m]   归并为有序的 TR2[s..m]   */
		MSort(SR, TR2, m + 1, t);	/* 将 SR[m+1..t] 归并为有序的 TR2[m+1..t] */

		Merge(SR, TR2, s, m, t);	/* 将 TR2[s..m] 和 TR2[m+1..t] 归并到TR1[s..t]中 */
	}

	return ;
}


/*
 * 相当于两个有序数组 归并到另一个数组中
 * SR 模拟两个数组(start mid end进行分割)
 * TR 模拟另一个数组
 * */
static void Merge(int *SR, int *TR, int start, int mid, int end)
{
	int 	front, back, k;

	for (back = mid + 1, front = start; 
			start <= mid && back <= end; 
			front++) 								/* 将 SR 中记录由小到大归并入 TR */
	{
		if (SR[start] < SR[back])	TR[front] = SR[start++];
		else						TR[front] = SR[back++];
	}

	if (start <= mid) {
		for (k = 0; k <= mid - start; k++)
			TR[back + k] = SR[start + k];			/* 将剩余的 SR[start..mid] 复制到 TR */
	}

	if (front <= end) {
		for (k = 0; k <= end - back; k++) 			/* 将剩余的 SR[j,,end] 复制到 TR */
			TR[back + k] = SR[front + k];
	}

	return ;
}
