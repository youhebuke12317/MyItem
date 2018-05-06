/**
* @file			Common.h
* @brief		排序算法
* @detils		定义排序算法字符数组结构
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月01日 星期二 14时43分07秒
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE	10
typedef struct {
	int 	r[MAXSIZE + 1];			// r[0] 用作哨兵或临时变量
	int 	length;
}SqList;

#define Swap(L, i, j)				\
	do {							\
		int temp  = (L)->r[i];		\
		(L)->r[i] = (L)->r[j]; 		\
		(L)->r[j] = temp;			\
	} while(0);

void BubbleSort_0(SqList *L);
void BubbleSort(SqList *L);
void BubbleSort_2(SqList *L);

void SelectSort(SqList *L);

void InsertSort(SqList *L);

void ShellSort(SqList *L);

void HeapSort(SqList *L);

void MergeSort(SqList *L);

int Offer_Partition(int *data, int length, int start, int end);
#endif


