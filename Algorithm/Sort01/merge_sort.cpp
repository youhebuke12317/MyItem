/**
* @file			merge_sort.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月06日 星期一 14时14分23秒
*/

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/*
 * @detail 归并排序算法
 * @param num	待排序数组
 * @param l		待排序数组开始位置
 * @param r		待排序数字结束位置
 * */
int merge_sort(int *num, int l, int r) {
	if (r - l < 1)	return -1;

	int mid = (l + r) >> 1;
	merge_sort(num, l, mid);
	merge_sort(num, mid + 1, r);

	int *temp = (int *)malloc(sizeof(int) * (r - l + 1));

	int p1 = l, p2 = mid + 1, k = 0;
	while (p1 <= mid || p2 <= r) {
		if ((p2 > r) || (p1 <= mid && num[p1] <= num[p2])) 
			temp[k++] = num[p1++];
		else temp[k++] = num[p2++];
	}

	memcpy(num + l, temp, (sizeof(int) * (r - l + 1)));
	free(temp);
	return 0;
}

int output(int *num, int n) {
	int flags = 1;
	printf("[");
	for (int i = 1; i < n; i++) {
		if (i) flags = (num[i] < num[i - 1]);
		printf("%d ", num[i]);
	}
	printf("]\n");
	return flags;
}

void test_output(int *num, int n) {
	if (output(num, n)) {
		printf("\033[31m FAIL \033[0m\n");
	} else {
		printf("\033[32m OK \033[0m\n");
	}
}

#define MAX_NUM_LEN		5000
int main() {
	srand(time(0));
	int num[MAX_NUM_LEN];
	for (int i = 0; i < MAX_NUM_LEN; i++) {
		num[i] = rand();
	}

	output(num, MAX_NUM_LEN);
	merge_sort(num, 0, MAX_NUM_LEN - 1);
	test_output(num, MAX_NUM_LEN);
}
