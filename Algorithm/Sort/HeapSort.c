/**
* @file			HeapSort.c
* @brief		堆排序
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月02日 星期三 09时06分36秒
*/

#include "Common.h"

static void HeapAdjust(SqList *, int, int);

/*
 * 排序之前数据
 * 		50  10  90  30  70  40  80  60  20
 *  
 * 经过堆排序之后：
 *		90  70  80  60  10  40  50  30  20
 *
 *		                90
 *		               / \
 *                    70  80
 *                   / \  / \
 *                  60 10 40 50
 *                 / \
 *                30 20
 *
 * 然后的操作 详见代码:
 *
 * */

void HeapSort(SqList *L)
{
	int		i;

	for (i = L->length / 2; i > 0; i--) {		/* 将L中的 r 构造成大顶堆 */
		HeapAdjust(L, i, L->length);
	}

	/*
	 * 上面已经成为将数据排列成了大顶堆 第一个数字始终是做大值
	 * */
	for (i = L->length; i > 1; i--) {		
		Swap(L, 1, i);							/* 将堆顶记录和当前未经排序的子序列的最后一个记录交换 */
		HeapAdjust(L, 1, i - 1);				/* 将 L->[1..i-1] 重新调整为大顶堆 */
	}

	return;
}

/*
 * 已知 L->r[s...m] 中记录的关键字除 L->r[s] 之外满足堆定义
 * 本函数调整 L->r[s] 的关键字 是的 L->r[s..m 成为一个大顶堆
 * */
static void HeapAdjust(SqList *L, int s, int m)
{
	int 	temp, j;

	temp = L->r[s];

	for(j = 2*s; j <=m; j *= 2) {						/* 沿关键字较大的孩子节点向下筛选, j 为 s 的左孩子, j+1 是 s 的右孩子 */

		// 如果 j 有右兄弟 即 s 有右孩子 并且 右孩子比左孩子大 j 为 s 孩子中较大的下标
		if (j < m && L->r[j] < L->r[j + 1])	++j;		/* j 为关键字中较大的记录的下标 */

		// temp 即 s, temp 比孩子节点还大 符合对结构 退出循环
		if (temp >= L->r[j])	break;					/* rc 应插入在位置 s 上 */

		L->r[s] = L->r[j];								/* 将较大的孩子节点放在父亲节点上 */

		s = j;											/* 以替换掉节点(s 的左右孩子)下标作为父节点 */
	}

	L->r[s] = temp;										/* 插入 */

	return ;
}
